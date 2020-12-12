# C/C++ style guide

### Headers and folder structure

- Use angle brackets for external libraries
```c
#include <string.h>
#include <littlefs/lfs.h>
```

- If including code from other folders, prepend the folders to make the code self-descriptive, prevent name conflicting, simplify the build
```c
#include "drivers/protocol/can.h"
#include <csp/csp.h>
#include <littlefs/lfs.h>
#include <firmware/drivers/mss_spi/mss_spi.h>
```

- In one module, if including code from the current folder, use relative path. This simplifies build/reusing of a module because only the path of the top-level file needs to be added to the build system. It also prevents name conflicting.
```c
#include "./can.h"
```

- Only make .cc file when it is supposed to be an executable (having a main function). This means you should write most of the code in header only libraries. This prevents the risks associated with keeping two files in sync.

- In header only libraries, tag a function/object with `/* export */` comment to show that the function/object is public.

- Try to only keep a header file under `include` folder, if it is supposed to be shared/used by other files.
