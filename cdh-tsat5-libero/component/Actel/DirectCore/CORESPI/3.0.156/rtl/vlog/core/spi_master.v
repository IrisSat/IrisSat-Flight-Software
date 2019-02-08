//-----------------------------------------------------------------------------
// (c) Copyright 2005 Actel Corporation
//
// name:		spi_master.v
// function:	SPI (Serial Peripheral Interface) Master
// comments:	best viewed with tabstops set to "4"
// history:		8/01/03  - TFB created
//				3/18/04  - TFB changed reset name to nreset, changed error
//				name to rx_error, other minor cleanups
//
// Rev:			2.1 24Jan05 TFB - Production
//
//-----------------------------------------------------------------------------

`timescale 1ns / 1ps

module spi_master (sysclk, nreset, enable, sck, miso, mosi, ss, cpol, cpha,
clocksel, rx_data_reg, rx_data_ready, rx_reg_re, tx_data_reg, tx_reg_empty,
busy, tx_reg_we, clear_error, rx_error);

// control signals
input			sysclk;			// Global clock
input			nreset;			// Act.low asynchronous reset
input			enable;			// Synchronous Enable
// SPI interface signals
output			sck;			// SPI Serial Clock signal
input			miso;			// SPI master input/slave output signal
output			mosi;			// SPI master output/slave input signal
// SPI Master internal signals
output			ss;				// SPI slave select output
input			cpol;			// SPI Serial Clock Polarity
input			cpha;			// SPI Serial Clock Phase
// SPI Serial Clock divisor select input
input	[2:0]	clocksel;
output	[7:0]	rx_data_reg;	// Rx data register
output			rx_data_ready;	// Status signal: rx data ready to read
input			rx_reg_re;		// Read Enable for rx_data_reg
input	[7:0]	tx_data_reg;	// Tx data register
output			tx_reg_empty;	// Status signal: tx reg can be written
// Status signal: SPI Master is busy transmitting data or has data in the
// tx_data_reg to be transmitted
output			busy;
input			tx_reg_we;		// Write enable for tx data register
input			clear_error;	// Syncronous reset for clearing rx error
output			rx_error;

// internal signals
wire			sck;
wire			ss;
wire			rx_data_ready;
wire			tx_reg_empty;
wire			busy;
wire			rx_error;
reg				mosi;
reg		[7:0]	rx_data_reg;
parameter[3:0]	IDLE=0,D7=1,D6=2,D5=3,D4=4,D3=5,D2=6,D1=7,D0=8,
				FINAL_CYCLE=9,LOAD_SHIFT_REG=10;
reg		[3:0]	state;
reg		[3:0]	next_state;
reg				i_sck;
reg				d_sck;
wire			c_sck;
reg				tsck;
reg				i_ss;
reg				tss;
reg				i_tx_reg_empty;
reg		[7:0]	clock_count;
reg				tx_data_ready;
reg				clear_tx_data_ready;
reg		[7:0]	tx_shift_reg;
reg		[7:0]	rx_shift_reg;
reg				shift_enable;
// TFB 2/5/04, not used
// signal rx_shift_enable      : std_logic;
// signal t_rx_shift_enable    : std_logic;
// signal d_rx_shift_enable    : std_logic;
reg				tx_shift_reg_load;
reg				d_tx_shift_reg_load;
reg				sck_enable;
reg				load_rx_data_reg;
reg				rx_error_i;
reg				rx_data_waiting;
// TFB 2/8/04
reg				rx_shift_enable1;
reg				rx_shift_enable2;
wire			rx_shift_enable;

    //------------------------------------
    // Serial Data Clock Generation.
    always @(posedge sysclk or negedge nreset)
    begin
        if (nreset == 1'b0)
        begin
            clock_count <= {8{1'b0}};
            i_sck <= 1'b0;
            d_sck <= 1'b0;
        end
        else
        begin
            if (enable == 1'b1)
            begin
                clock_count <= clock_count + 8'b00000001;
            end 
            case (clocksel)
                3'b000 :
                            begin
                                i_sck <= clock_count[0];	// SysClk /2
                            end
                3'b001 :
                            begin
                                i_sck <= clock_count[1];	// SysClk /4
                            end
                3'b010 :
                            begin
                                i_sck <= clock_count[2];	// SysClk /8
                            end
                3'b011 :
                            begin
                                i_sck <= clock_count[3];	// SysClk /16
                            end
                3'b100 :
                            begin
                                i_sck <= clock_count[4];	// SysClk /32
                            end
                3'b101 :
                            begin
                                i_sck <= clock_count[5];	// SysClk /64
                            end
                3'b110 :
                            begin
                                i_sck <= clock_count[6];	// SysClk /128
                            end
                3'b111 :
                            begin
                                i_sck <= clock_count[7];	// SysClk /256
                            end
                // TFB 2/5/04
                //when others => i_sck <= '0';
                default :
                            begin
                                i_sck <= clock_count[0];
                            end
            endcase 
            d_sck <= i_sck;
        end 
    end 
    assign c_sck = (cpha == 1'b1 & cpol == 1'b0) ? sck_enable & d_sck    :
                   (cpha == 1'b1 & cpol == 1'b1) ? ~(sck_enable & d_sck) :
                   (cpha == 1'b0 & cpol == 1'b0) ? sck_enable & (~d_sck) :
                   ~(sck_enable & (~d_sck));

    // TFB modified 2/5/04, cpol is reset to '0' at higher level, so sync. reset
    // not necessary here ...
    //-----------------------------------------------
    //   process (sysclk)
    //   begin
    //      if rising_edge(sysclk) then
    //         if nreset = '0' then
    //            tsck <= cpol;
    //         else
    //            tsck <= c_sck;
    //         end if;
    //      end if;
    //   end process;
    //-----------------------------------------------
    always @(posedge sysclk or negedge nreset)
    begin
        if (nreset == 1'b0)
        begin
            tsck <= 1'b0;
        end
        else
        begin
            tsck <= c_sck;
        end 
    end 

    //-----------------------------------------------
    always @(posedge sysclk or negedge nreset)
    begin
        if (nreset == 1'b0)
        begin
            tss <= 1'b1;
        end
        else
        begin
            tss <= i_ss;
        end 
    end 
    assign sck = tsck;
    assign ss = tss;

    //---------------
    // Control FSM.
    always @(posedge sysclk or negedge nreset)
    begin
        if (nreset == 1'b0)
        begin
            state <= IDLE;
        end
        else
        begin
            if (enable == 1'b1)
            begin
                state <= next_state;
            end
            else
            begin
                state <= IDLE;
            end 
        end 
    end 

    always @(state or tx_data_ready or i_sck or d_sck)
    begin
        clear_tx_data_ready <= 1'b0;
        shift_enable <= 1'b0;
        tx_shift_reg_load <= 1'b0;
        i_ss <= 1'b1;
        sck_enable <= 1'b0;
        load_rx_data_reg <= 1'b0;
        case (state)
            IDLE :
            begin
                if (tx_data_ready == 1'b1 & i_sck == 1'b1 & d_sck == 1'b0)
                begin
                    clear_tx_data_ready <= 1'b1;
                    next_state <= LOAD_SHIFT_REG;
                end
                else
                begin
                    next_state <= IDLE;
                end 
            end
            LOAD_SHIFT_REG :
            begin
                tx_shift_reg_load <= 1'b1;
                if (d_sck == 1'b0)
                begin
                    i_ss <= 1'b0;
                    if (i_sck == 1'b1)
                    begin
                        next_state <= D7;
                    end
                    else
                    begin
                        next_state <= LOAD_SHIFT_REG;
                    end 
                end
                else
                begin
                    next_state <= LOAD_SHIFT_REG;
                end 
            end
            D7 :
            begin
                i_ss <= 1'b0;
                sck_enable <= 1'b1;
                if (i_sck == 1'b1 & d_sck == 1'b0)
                begin
                    shift_enable <= 1'b1;
                    next_state <= D6;
                end
                else
                begin
                    next_state <= D7;
                end 
            end
            D6 :
            begin
                i_ss <= 1'b0;
                sck_enable <= 1'b1;
                if (i_sck == 1'b1 & d_sck == 1'b0)
                begin
                    shift_enable <= 1'b1;
                    next_state <= D5;
                end
                else
                begin
                    next_state <= D6;
                end 
            end
            D5 :
            begin
                i_ss <= 1'b0;
                sck_enable <= 1'b1;
                if (i_sck == 1'b1 & d_sck == 1'b0)
                begin
                    shift_enable <= 1'b1;
                    next_state <= D4;
                end
                else
                begin
                    next_state <= D5;
                end 
            end
            D4 :
            begin
                i_ss <= 1'b0;
                sck_enable <= 1'b1;
                if (i_sck == 1'b1 & d_sck == 1'b0)
                begin
                    shift_enable <= 1'b1;
                    next_state <= D3;
                end
                else
                begin
                    next_state <= D4;
                end 
            end
            D3 :
            begin
                i_ss <= 1'b0;
                sck_enable <= 1'b1;
                if (i_sck == 1'b1 & d_sck == 1'b0)
                begin
                    shift_enable <= 1'b1;
                    next_state <= D2;
                end
                else
                begin
                    next_state <= D3;
                end 
            end
            D2 :
            begin
                i_ss <= 1'b0;
                sck_enable <= 1'b1;
                if (i_sck == 1'b1 & d_sck == 1'b0)
                begin
                    shift_enable <= 1'b1;
                    next_state <= D1;
                end
                else
                begin
                    next_state <= D2;
                end 
            end
            D1 :
            begin
                i_ss <= 1'b0;
                sck_enable <= 1'b1;
                if (i_sck == 1'b1 & d_sck == 1'b0)
                begin
                    shift_enable <= 1'b1;
                    next_state <= D0;
                end
                else
                begin
                    next_state <= D1;
                end 
            end
            D0 :
            begin
                i_ss <= 1'b0;
                sck_enable <= 1'b1;
                if (i_sck == 1'b1 & d_sck == 1'b0)
                begin
                    shift_enable <= 1'b1;
                    next_state <= FINAL_CYCLE;
                end
                else
                begin
                    next_state <= D0;
                end 
            end
            FINAL_CYCLE :
            begin
                if (d_sck == 1'b1)
                begin
                    i_ss <= 1'b0;
                    next_state <= FINAL_CYCLE;
                end
                else
                begin
                    load_rx_data_reg <= 1'b1;
                    i_ss <= 1'b1;
                    if (tx_data_ready == 1'b1 & i_sck == 1'b1)
                    begin
                        clear_tx_data_ready <= 1'b1;
                        next_state <= LOAD_SHIFT_REG;
                    end
                    else
                    begin
                        next_state <= IDLE;
                    end 
                end 
            end
        endcase 
    end 

    // TFB 2/5/04, not used
    //   ----------------------
    //   -- RX shift register.
    //   process(sysclk, nreset)
    //   begin
    //      if nreset = '0' then
    //         d_rx_shift_enable <= '0';
    //      elsif rising_edge(sysclk) then
    //         d_rx_shift_enable <= t_rx_shift_enable;
    //      end if;
    //   end process;
    //   t_rx_shift_enable <= (not i_ss) and (not i_sck) and d_sck;
    //----------------------------------------------------------
    // TFB added 2/8/04
    always @(i_ss or c_sck or tsck or cpol or cpha)
    begin
        if (i_ss == 1'b0)
        begin
            if ((cpol ^ cpha) == 1'b0)
            begin
                rx_shift_enable1 <= c_sck & (~tsck);
            end
            else
            begin
                rx_shift_enable1 <= (~c_sck) & tsck;
            end 
        end
        else
        begin
            rx_shift_enable1 <= 1'b0;
        end 
    end 

    // delay rx_shift_enable by 1 cycle for fastest clock rate (clocksel="000")
    always @(posedge sysclk or negedge nreset)
    begin
        if (nreset == 1'b0)
        begin
            rx_shift_enable2 <= 1'b0;
        end
        else
        begin
            rx_shift_enable2 <= rx_shift_enable1;
        end 
    end 
    assign rx_shift_enable = (clocksel == 3'b000) ? rx_shift_enable2 :
                                                    rx_shift_enable1;

    //----------------------------------------------------------
    always @(posedge sysclk or negedge nreset)
    begin
        if (nreset == 1'b0)
        begin
            rx_shift_reg <= {8{1'b0}};
        end
        else
        begin
            // TFB modified 2/8/04 to correct for CLKSEL=0
            //if d_rx_shift_enable = '1' then
            //if t_rx_shift_enable = '1' then
            if (rx_shift_enable == 1'b1)
            begin
                rx_shift_reg[0]		<= miso;
                rx_shift_reg[7:1]	<= rx_shift_reg[6:0];
            end 
        end 
    end 

    //-------------------
    // TX Shift register.
    always @(posedge sysclk or negedge nreset)
    begin
        if (nreset == 1'b0)
        begin
            tx_shift_reg <= {8{1'b0}};
            mosi <= 1'b0;
        end
        else
        begin
            if (tx_shift_reg_load == 1'b1)
            begin
                tx_shift_reg <= tx_data_reg;
            end
            else if (shift_enable == 1'b1)
            begin
                // data transfer cycles.
                tx_shift_reg[7:1]	<= tx_shift_reg[6:0];
            end 
            mosi <= tx_shift_reg[7];
        end 
    end 

    //---------------------
    // RX data register.
    always @(posedge sysclk or negedge nreset)
    begin
        if (nreset == 1'b0)
        begin
            rx_data_reg <= {8{1'b0}};
        end
        else
        begin
            if (enable == 1'b1)
            begin
                if (load_rx_data_reg == 1'b1)
                begin
                    rx_data_reg <= rx_shift_reg;
                end 
            end 
        end 
    end 

    //--------------------------------
    // Generate rx_data_waiting flag.
    always @(posedge sysclk or negedge nreset)
    begin
        if (nreset == 1'b0)
        begin
            rx_data_waiting <= 1'b0;
            rx_error_i <= 1'b0;
        end
        else
        begin
            if (rx_reg_re == 1'b1)
            begin
                rx_data_waiting <= 1'b0;
            end
            else if (clear_error == 1'b1)
            begin
                rx_error_i <= 1'b0;
            end
            else if (load_rx_data_reg == 1'b1)
            begin
                if (rx_data_waiting == 1'b1)
                begin
                    rx_error_i <= 1'b1;
                end
                else
                begin
                    rx_data_waiting <= 1'b1;
                end 
            end 
        end 
    end 
    assign rx_error = rx_error_i;
    assign rx_data_ready = rx_data_waiting;

    //--------------------------------
    // Generate tx_data_ready flag.
    always @(posedge sysclk or negedge nreset)
    begin
        if (nreset == 1'b0)
        begin
            tx_data_ready <= 1'b0;
            i_tx_reg_empty <= 1'b1;
            d_tx_shift_reg_load <= 1'b0;
        end
        else
        begin
            if (tx_reg_we == 1'b1)
            begin
                tx_data_ready <= 1'b1;
                i_tx_reg_empty <= 1'b0;
            end
            else if (clear_tx_data_ready == 1'b1)
            begin
                tx_data_ready <= 1'b0;
            end
            else if (tx_shift_reg_load == 1'b0 & d_tx_shift_reg_load == 1'b1)
            begin
                i_tx_reg_empty <= 1'b1;
            end 
            d_tx_shift_reg_load <= tx_shift_reg_load;
        end 
    end 
    assign tx_reg_empty = i_tx_reg_empty;

    //---------------------
    // Generate Busy flag.
    assign busy = (tss == 1'b0 | (~i_tx_reg_empty) == 1'b1 | state != IDLE) ?
                  1'b1 : 1'b0;

endmodule
