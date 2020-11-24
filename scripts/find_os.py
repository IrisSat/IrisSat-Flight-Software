import os
import platform
import sysconfig

is_windows = (os.name == 'nt' or (os.getenv('SYSTEMROOT') is not None and 'windows' in os.getenv('SYSTEMROOT').lower()) or (os.getenv('COMSPEC') is not None and 'windows' in os.getenv('COMSPEC').lower()))
is_msys = os.getenv('MSYSTEM')
is_mingw = sysconfig.get_platform() == 'mingw'
is_mac = platform.mac_ver()[0] != ''
is_linux = not is_mac and (platform.system() == 'Linux')
is_unix = (is_linux or is_mac)
