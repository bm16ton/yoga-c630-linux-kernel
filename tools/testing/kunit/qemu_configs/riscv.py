from ..qemu_config import QemuArchParams
import os
import os.path
import sys

<<<<<<< HEAD
OPENSBI_FILE = 'opensbi-riscv64-generic-fw_dynamic.bin'
OPENSBI_PATH = '/usr/share/qemu/' + OPENSBI_FILE

if not os.path.isfile(OPENSBI_PATH):
	print('\n\nOpenSBI bios was not found in "' + OPENSBI_PATH + '".\n'
	      'Please ensure that qemu-system-riscv is installed, or edit the path in "qemu_configs/riscv.py"\n')
	sys.exit()
=======
GITHUB_OPENSBI_URL = 'https://github.com/qemu/qemu/raw/master/pc-bios/opensbi-riscv64-generic-fw_dynamic.bin'
OPENSBI_FILE = os.path.basename(GITHUB_OPENSBI_URL)

if not os.path.isfile(OPENSBI_FILE):
	print('\n\nOpenSBI file is not in the current working directory.\n'
	      'Would you like me to download it for you from:\n' + GITHUB_OPENSBI_URL + ' ?\n')
	response = input('yes/[no]: ')
	if response.strip() == 'yes':
		os.system('wget ' + GITHUB_OPENSBI_URL)
	else:
		sys.exit()
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2

QEMU_ARCH = QemuArchParams(linux_arch='riscv',
			   kconfig='''
CONFIG_SOC_VIRT=y
CONFIG_SERIAL_8250=y
CONFIG_SERIAL_8250_CONSOLE=y
CONFIG_SERIAL_OF_PLATFORM=y
CONFIG_RISCV_SBI_V01=y
CONFIG_SERIAL_EARLYCON_RISCV_SBI=y''',
			   qemu_arch='riscv64',
			   kernel_path='arch/riscv/boot/Image',
			   kernel_command_line='console=ttyS0',
			   extra_qemu_params=[
					   '-machine', 'virt',
					   '-cpu', 'rv64',
<<<<<<< HEAD
					   '-bios', OPENSBI_PATH])
=======
					   '-bios', 'opensbi-riscv64-generic-fw_dynamic.bin'])
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
