import os
import platform
import sysconfig

is_windows = (os.name == 'nt' or (os.getenv('SYSTEMROOT') is not None and 'windows' in os.getenv('SYSTEMROOT').lower()) or (os.getenv('COMSPEC') is not None and 'windows' in os.getenv('COMSPEC').lower()))
is_msys = os.getenv('MSYSTEM')
is_mingw = sysconfig.get_platform() == 'mingw'
is_mac = platform.mac_ver()[0] != ''
is_linux = not is_mac and (platform.system() == 'Linux')
is_unix = (is_linux or is_mac)


import tempfile
import shutil
import subprocess
import glob

# function to download a git repository
def download_git_branch(rev, url, download_dir, folder_name=""):
    print(f"Downloading {url} {rev} to {download_dir}/{folder_name}...")

    # Find the name of git basename folder
    git_basename = os.path.splitext(os.path.basename(url))[0]

    if folder_name == "":
        folder_name = git_basename

    final_path = os.path.join(download_dir, folder_name)

    # clean up destination folder
    shutil.rmtree(final_path, ignore_errors=True)

    # download the repo to a temporary folder
    temp_dir = tempfile.mkdtemp()
    download_path = os.path.join(temp_dir, git_basename)
    subprocess.run(f"git clone --depth 1 --branch {rev} {url}", shell=True, check=True, cwd=temp_dir)

    # delete .git folder
    git_folder = glob.glob(f"{temp_dir}/*/.git")[0]
    tmp_git = tempfile.mkdtemp()
    shutil.move(git_folder, tmp_git)
    shutil.rmtree(tmp_git, ignore_errors=True)

    # move to the destination
    shutil.move(download_path, download_dir)
