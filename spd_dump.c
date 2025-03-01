/*
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
*/
#include "common.h"
#include "GITVER.h"

void print_help(void)
{
	DBG_LOG(
		"说明\n"
		"\tspd_dump [选项] [指令] [退出指令]\n"
		"\n例子\n"
		"\t单线模式\n"
		"\t\tspd_dump --wait 300 fdl /path/to/fdl1 fdl1_addr fdl /path/to/fdl2 fdl2_addr exec path savepath r all_lite reset\n"
		"\tInteractive mode\n"
		"\t\tspd_dump --wait 300 fdl /path/to/fdl1 fdl1_addr fdl /path/to/fdl2 fdl2_addr exec\n"
		"\t成功后应提示 FDL2>\n"
		"\n选项\n"
		"\t--wait <秒数>\n"
		"\t\t指定等待设备连接的时间。\n"
		"\t--stage <数字>|-r|--reconnect\n"
		"\t\t尝试重新连接在brom/fdl1/fdl2阶段的设备。数字输入多少无所谓（甚至非数字也行）。\n"
		"\t\t(处于brom/fdl1阶段的设备可以无限次重新连接，但在fdl2阶段只能重新连接一次)\n"
		"\t--verbose <等级>\n"
		"\t\t设置屏幕日志的详细程度（支持0、1或2，不影响文件日志）。\n"
		"\t--kick\n"
		"\t\t使用 boot_diag->cali_diag->dl_diag 途径连接设备。\n"
		"\t--kickto <mode>\n"
		"\t\t使用boot_diag->custom_diag 途径连接设备。支持的模式为0-127。\n"
		"\t\t(模式0为ums9621平台的新版--kickto 2, 模式 1 = cali_diag, 模式 2 = dl_diag; 并非所有设备都支持模式 2)\n"
		"\t-?|-h|--help\n"
		"\t\t显示使用帮助。\n"
		"\n运行时命令\n"
		"\tverbose <等级>\n"
		"\t\t设置屏幕日志的详细程度（支持0、1或2，不影响文件日志）。\n"
		"\ttimeout <毫秒>\n"
		"\t\t设置读写等待的超时时间（毫秒）\n"
		"\tbaudrate [波特率]\n\t\t(仅限Windows SPRD驱动程序和brom/fdl2阶段)\n"
		"\t\t支持的波特率为57600、115200、230400、460800、921600、1000000、2000000、3250000和4000000。\n"
		"\t\t在u-boot/littlekernel源代码中，只列出了115200、230400、460800和921600。\n"
		"\texec_addr [addr]\n\t\t（仅限brom阶段）\n"
		"\t\t将 customexec_no_verify_addr.bin 发送到指定的内存地址，以绕过brom对 splloader/fdl1 的签名验证。\n"
		"\t\t用于CVE-2022-38694。\n"
		"\tfdl <文件路径> <地址>\n"
		"\t\t将文件（splloader,fdl1,fdl2,sml,trustos,teecfg）发送到指定的内存地址。\n"
		"\texec\n"
		"\t\t在fdl1阶段执行已发送的文件。通常与sml或fdl2（也称为uboot/lk）一起使用。\n"
		"\tpath [保存路径]\n"
		"\t\t更改r,read_part(s),read_flash和read_mem命令的保存目录。\n"
		"\tnand_id [id]\n"
		"\t\t指定nand芯片的4th id参数，该参数影响read_part(s)分区大小的算法，默认值为0x15。\n"
		"\trawdata {0,2}\n\t\t（仅限fdl2阶段）\n"
		"\t\trawdata协议用于加速w和write_part命令，当rawdata为2时，写入速度与blk_size无关\n"
		"\t\trawdata协议用于加速w和write_part命令，当rawdata为2时，写入速度与blk_size无关（依赖于u-boot/lk，因此默认2的可以改0/2，默认0的不能改2，注意：暂时不支持默认rawdata=1的设备）\n"
		"\tblk_size <byte>\n\t\t（仅限fdl2阶段）\n"
		"\t\t设置块大小，最大为65535字节。此选项用于加快r、w、read_part(s)和write_part(s)命令的速度。\n"
		"\tr all|分区名称|分区id\n"
		"\t\t当分区表可用时：\n"
		"\t\t\tr all: 全盘备份 (跳过 blackbox, cache, userdata)\n"
		"\t\t\tr all_lite: 全盘备份 (非活动插槽分区, blackbox, cache, and userdata)\n"
		"\t\tW当分区表不可用时:\n"
		"\t\t\tr 将自动计算部件大小（支持emmc/ufs上的所有分区，NAND上仅支持ubipac分区）\n"
		"\tread_part <分区名称|分区id> <偏移量> <大小> <保存路径>\n"
		"\t\t以给定的偏移量和大小将特定分区读取到文件中。\n"
		"\t\t（在nand上读取ubi）read_part system 0 ubi40m system.bin\n"
		"\tread_parts <分区表文件>\n"
		"\t\t按照XML类型分区列表从设备读取分区（如果文件名以“ubi”开头，则将使用NAND ID计算大小）\n"
		"\tw|write_part 分区名称|分区id <文件路径>\n"
		"\t\t将指定的文件写入分区。\n"
		"\twrite_parts <保存文件夹路径>\n"
		"\t\t写入指定文件夹下所有文件到设备分区，通常由read_parts得到。\n"
		"\te|erase_part 分区名称|分区id\n"
		"\t\t擦除指定分区。\n"
		"\tpartition_list <分区表路径>\n"
		"\t\t读取emmc/ufs上的分区列表，并非所有fdl2都支持此命令。\n"
		"\trepartition <xml分区表文件>\n"
		"\t\根据XML类型分区列表重新分区。\n"
		"\tp|print\n"
		"\t\t打印分区列表\n"
		"\tverity {0,1}\n"
		"\t\t在Android 10(+)上禁用或启用dm-verity\n"
		"\n退出指令\n"
		"\t(一般于FDL2阶段可用可用；只有很新的FDL1才支持)\n"
		"\treset 重启\n"
		"\tpoweroff 关机（在设备断开usb后）\n"
	);
}

#define REOPEN_FREQ 2
extern char savepath[ARGV_LEN];
extern DA_INFO_T Da_Info;
int bListenLibusb = -1;
int gpt_failed = 1;
int m_bOpened = 0;
int fdl1_loaded = 0;
int fdl2_executed = 0;
int selected_ab = -1;
uint64_t fblk_size = 0;
int main(int argc, char **argv) {
	spdio_t *io = NULL; int ret, i, in_quote;
	int wait = 30 * REOPEN_FREQ;
	int argcount = 0, stage = -1, nand_id = DEFAULT_NAND_ID;
	int nand_info[3];
	int keep_charge = 1, end_data = 1, blk_size = 0, skip_confirm = 1, highspeed = 0;
	unsigned exec_addr = 0, baudrate = 0;
	char *temp;
	char str1[(ARGC_MAX - 1) * ARGV_LEN];
	char **str2;
	char *execfile;
	char fn_partlist[40];
	int bootmode = -1, at = 0;
	int part_count = 0;
	partition_t* ptable = NULL;
#if !USE_LIBUSB
	extern DWORD curPort;
	extern DWORD* ports;
#else
	extern libusb_device* curPort;
	extern libusb_device** ports;
#endif
	execfile = malloc(ARGV_LEN);
	if (!execfile) ERR_EXIT("malloc failed\n");

	io = spdio_init(0);
#if USE_LIBUSB
#ifdef __ANDROID__
	int xfd = -1; // This store termux gived fd
	//libusb_device_handle *handle; // Use spdio_t.dev_handle
	libusb_device* device;
	struct libusb_device_descriptor desc;
	libusb_set_option(NULL, LIBUSB_OPTION_NO_DEVICE_DISCOVERY);
#endif
	ret = libusb_init(NULL);
	if (ret < 0)
		ERR_EXIT("libusb_init failed: %s\n", libusb_error_name(ret));
#else
	io->handle = createClass();
	call_Initialize(io->handle);
#endif
	DBG_LOG("分支:%s, sha1:%s\n", GIT_VER, GIT_SHA1);
	sprintf(fn_partlist, "partition_%lld.xml", (long long)time(NULL));
	while (argc > 1) {
		if (!strcmp(argv[1], "--wait")) {
			if (argc <= 2) ERR_EXIT("bad option\n");
			wait = atoi(argv[2]) * REOPEN_FREQ;
			argc -= 2; argv += 2;
		} else if (!strcmp(argv[1], "--verbose")) {
			if (argc <= 2) ERR_EXIT("bad option\n");
			io->verbose = atoi(argv[2]);
			argc -= 2; argv += 2;
		} else if (!strcmp(argv[1], "--stage")) {
			if (argc <= 2) ERR_EXIT("bad option\n");
			stage = 99;
			argc -= 2; argv += 2;
		} else if (strstr(argv[1], "-r")) {
			if (argc <= 1) ERR_EXIT("bad option\n");
			stage = 99;
			argc -= 1; argv += 1;
		} else if (strstr(argv[1], "help") || strstr(argv[1], "-h") || strstr(argv[1], "-?")) {
			if (argc <= 1) ERR_EXIT("bad option\n");
			print_help();
			return 0;
#ifdef __ANDROID__
		} else if (!strcmp(argv[1], "--usb-fd")) { // Termux spec
			if (argc <= 2) ERR_EXIT("bad option\n");
			xfd = atoi(argv[argc - 1]);
			argc -= 2; argv += 1;
#endif
		} else if (!strcmp(argv[1], "--kick")) {
			if (argc <= 1) ERR_EXIT("bad option\n");
			at = 1;
			argc -= 1; argv += 1;
		} else if (!strcmp(argv[1], "--kickto")) {
			if (argc <= 2) ERR_EXIT("bad option\n");
			bootmode = atoi(argv[2]); at = 0;
			argc -= 2; argv += 2;
		} else break;
	}

	if (stage == 99) { bootmode = -1; at = 0; }
#if !USE_LIBUSB
	bListenLibusb = 0;
	if (at || bootmode >= 0)
	{
		io->hThread = CreateThread(NULL, 0, ThrdFunc, NULL, 0, &io->iThread);
		if (io->hThread == NULL) return -1;
		ChangeMode(io, wait / REOPEN_FREQ * 1000, bootmode, at);
		wait = 30 * REOPEN_FREQ;
		stage = -1;
	}
	else
	{
		curPort = FindPort("SPRD U2S Diag");
		if (curPort)
		{
			for (DWORD* port = ports; *port != 0; port++)
			{
				if (call_ConnectChannel(io->handle, *port))
				{
					curPort = *port;
					break;
				}
			}
			if (!m_bOpened) curPort = 0;
			free(ports);
			ports = NULL;
		}
	}
#else
	if (!libusb_has_capability(LIBUSB_CAP_HAS_HOTPLUG)) { DBG_LOG("此平台上不支持热插拔\n"); bListenLibusb = 0; bootmode = -1; at = 0; }
	if (at || bootmode >= 0)
	{
		startUsbEventHandle();
		ChangeMode(io, wait / REOPEN_FREQ * 1000, bootmode, at);
		wait = 30 * REOPEN_FREQ;
		stage = -1;
	}
	else
	{
		curPort = FindPort();
		if (curPort != NULL)
		{
			for (libusb_device** port = ports; *port != NULL; port++)
			{
				if (libusb_open(*port, &io->dev_handle) >= 0) {
					call_Initialize_libusb(io);
					curPort = *port;
					break;
				}
			}
			if (!m_bOpened) curPort = 0;
			free(ports);
			ports = NULL;
		}
	}
	if (bListenLibusb < 0) startUsbEventHandle();
#endif
#if _WIN32
	if (!bListenLibusb) {
		if (io->hThread == NULL) io->hThread = CreateThread(NULL, 0, ThrdFunc, NULL, 0, &io->iThread);
		if (io->hThread == NULL) return -1;
	}
#endif
#ifdef __ANDROID__
	DBG_LOG("尝试转换Termux传输的usb端口fd\n");
	// handle
	if (xfd < 0)
		ERR_EXIT("Example: termux-usb -e \"./spd_dump --usb-fd\" /dev/bus/usb/xxx/xxx\n"
			"run on android need provide --usb-fd\n");

	if (libusb_wrap_sys_device(NULL, (intptr_t)xfd, &io->dev_handle))
		ERR_EXIT("libusb_wrap_sys_device exit unconditionally!\n");

	device = libusb_get_device(io->dev_handle);
	if (libusb_get_device_descriptor(device, &desc))
		ERR_EXIT("libusb_get_device exit unconditionally!");

	DBG_LOG("Vendor ID: %04x\nProduct ID: %04x\n", desc.idVendor, desc.idProduct);
	if (desc.idVendor != 0x1782 || desc.idProduct != 0x4d00) {
		ERR_EXIT("It seems spec device not a spd device!\n");
	}
	call_Initialize_libusb(io);
#else
	if (!m_bOpened) DBG_LOG("正在等待dl_diag连接 (%ds)\n", wait / REOPEN_FREQ);
	for (i = 0; ; i++) {
#if USE_LIBUSB
		if (bListenLibusb) { if (curPort) break; }
		else {
			io->dev_handle = libusb_open_device_with_vid_pid(NULL, 0x1782, 0x4d00);
			if (io->dev_handle) {
				call_Initialize_libusb(io);
				break;
			}
		}
		if (i >= wait)
			ERR_EXIT("libusb_open_device failed\n");
#else
		if (io->verbose) DBG_LOG("CurTime: %.1f, CurPort: %d\n", (float)i / REOPEN_FREQ, curPort);
		if (curPort) break;
		if (i >= wait)
			ERR_EXIT("find port failed\n");
#endif
		usleep(1000000 / REOPEN_FREQ);
	}
#if USE_LIBUSB
	if (!m_bOpened)
	{
		if (libusb_open(curPort, &io->dev_handle) >= 0) call_Initialize_libusb(io);
		else ERR_EXIT("Connection failed\n");
	}
#else
	if (!m_bOpened) if (!call_ConnectChannel(io->handle, curPort)) ERR_EXIT("Connection failed\n");
#endif
#endif
	io->flags |= FLAGS_TRANSCODE;
	io->flags &= ~FLAGS_CRC16;
	if (stage != -1) encode_msg(io, BSL_CMD_CONNECT, NULL, 0);
	else encode_msg(io, BSL_CMD_CHECK_BAUD, NULL, 1);
	for (i = 0; ; i++) {
		if (io->recv_buf[2] == BSL_REP_VER)
		{
			ret = BSL_REP_VER;
			io->flags |= FLAGS_CRC16;
			memcpy(io->raw_buf + 4, io->recv_buf + 5, 5);
			io->raw_buf[2] = 0;
			io->raw_buf[3] = 5;
		} else {
			send_msg(io);
			recv_msg(io);
			ret = recv_type(io);
		}
		if (ret == BSL_REP_ACK || ret == BSL_REP_VER || ret == BSL_REP_VERIFY_ERROR)
		{
			if (ret == BSL_REP_VER)
			{
				if (fdl1_loaded == 1)
				{
					DBG_LOG("检查波特率 FDL1\n");
					if (!memcmp(io->raw_buf + 4, "SPRD4", 5)) fdl2_executed = -1;
				}
				else
				{
					DBG_LOG("检查波特率 bootrom\n");
					if (!memcmp(io->raw_buf + 4, "SPRD4", 5)) { fdl1_loaded = -1; fdl2_executed = -1; }
				}
				DBG_LOG("BSL_REP_VER: ");
				print_string(stderr, io->raw_buf + 4, READ16_BE(io->raw_buf + 2));

				encode_msg(io, BSL_CMD_CONNECT, NULL, 0);
				if (send_and_check(io)) exit(1);
			}
			else if (ret == BSL_REP_VERIFY_ERROR)
			{
				encode_msg(io, BSL_CMD_CONNECT, NULL, 0);
				if (fdl1_loaded != 1)
				{
					if (send_and_check(io)) exit(1);
				}
				else { i = -1; continue; }
			}

			if (fdl1_loaded == 1)
			{
				DBG_LOG("连接到 FDL1\n");
				if (keep_charge) {
					encode_msg(io, BSL_CMD_KEEP_CHARGE, NULL, 0);
					if (!send_and_check(io)) DBG_LOG("保持充电 FDL1\n");
				}
			}
			else DBG_LOG("连接到 bootrom\n");
			break;
		}
		else if (ret == BSL_REP_UNSUPPORTED_COMMAND)
		{
			encode_msg(io, BSL_CMD_DISABLE_TRANSCODE, NULL, 0);
			if (!send_and_check(io)) {
				io->flags &= ~FLAGS_TRANSCODE;
				DBG_LOG("禁用转码\n");
			}
			fdl2_executed = 1;
			break;
		}
		else if (i == 4)
		{
			if (stage != -1) ERR_EXIT("检测到错误的命令或错误的模式，请按电源键和音量+键7-10秒重新启动手机。\n");
			else { encode_msg(io, BSL_CMD_CONNECT, NULL, 0); stage++; i = -1; }
		}
	}

	while (1) {
		if (argc > 1)
		{
			str2 = (char**)malloc(argc * sizeof(char*));
			for (i = 1; i < argc; i++) str2[i] = argv[i];
			argcount = argc;
			in_quote = -1;
		}
		else
		{
			char ifs = '"';
			str2 = (char**)malloc(ARGC_MAX * sizeof(char*));
			memset(str1, 0, sizeof(str1));
			argcount = 0;
			in_quote = 0;

			if (fdl2_executed > 0)
				DBG_LOG("FDL2 >");
			else if (fdl1_loaded > 0)
				DBG_LOG("FDL1 >");
			else
				DBG_LOG("BROM >");
			ret = scanf("%[^\n]", str1);
			while ('\n' != getchar());

			temp = strtok(str1, " ");
			while (temp)
			{
				if (!in_quote) {
					argcount++;
					if (argcount == ARGC_MAX) break;
					str2[argcount] = (char*)malloc(ARGV_LEN);
					if (!str2[argcount]) ERR_EXIT("malloc failed\n");
					memset(str2[argcount], 0, ARGV_LEN);
				}
				if (temp[0] == '\'') ifs = '\'';
				if (temp[0] == ifs)
				{
					in_quote = 1;
					temp += 1;
				}
				else if (in_quote)
				{
					strcat(str2[argcount], " ");
				}

				if (temp[strlen(temp) - 1] == ifs)
				{
					in_quote = 0;
					temp[strlen(temp) - 1] = 0;
				}

				strcat(str2[argcount], temp);
				temp = strtok(NULL, " ");
			}
			argcount++;
		}
		if (argcount == 1)
		{
			str2[1] = malloc(1);
			if (str2[1]) str2[1][0] = '\0';
			else ERR_EXIT("malloc failed\n");
			argcount++;
		}

		if (!strcmp(str2[1], "sendloop")) {
			const char* fn; uint32_t addr = 0; FILE* fi;
			if (argcount <= 3) { DBG_LOG("sendloop <文件> <地址>\n"); argc -= 3; argv += 3; continue; }

			fn = str2[2];
			fi = fopen(fn, "r");
			if (fi == NULL) { DBG_LOG("文件不存在。\n"); argc -= 3; argv += 3; continue; }
			else fclose(fi);
			addr = strtoul(str2[3], NULL, 0);
			while (1) {
				send_file(io, fn, addr, 0, 528);
				addr -= 8;
			}
			argc -= 3; argv += 3;
		}
		else if (!strcmp(str2[1], "send")) {
			const char* fn; uint32_t addr = 0; FILE* fi;
			if (argcount <= 3) { DBG_LOG("send <文件> <地址>\n"); argc -= 3; argv += 3; continue; }

			fn = str2[2];
			fi = fopen(fn, "r");
			if (fi == NULL) { DBG_LOG("文件不存在。\n"); argc -= 3; argv += 3; continue; }
			else fclose(fi);
			addr = strtoul(str2[3], NULL, 0);
			send_file(io, fn, addr, 0, 528);
			argc -= 3; argv += 3;
		}
		else if (!strncmp(str2[1], "fdl", 3) || !strncmp(str2[1], "loadfdl", 7)) {
			const char *fn; uint32_t addr = 0; FILE *fi;
			int addr_in_name = !strncmp(str2[1], "loadfdl", 7);
			int argchange;

			fn = str2[2];
			if (addr_in_name) {
				argchange = 2;
				if (argcount <= argchange) { DBG_LOG("loadfdl <文件>\n"); argc -= argchange; argv += argchange; continue; }
				char* pos = NULL, * last_pos = NULL;

				pos = strstr(fn, "0X");
				while (pos) {
					last_pos = pos;
					pos = strstr(pos + 2, "0X");
				}
				if (last_pos == NULL) {
					pos = strstr(fn, "0x");
					while (pos) {
						last_pos = pos;
						pos = strstr(pos + 2, "0x");
					}
				}
				if (last_pos) addr = strtoul(last_pos, NULL, 16);
				else DBG_LOG("\"0x\" 在名称中找不到。\n");
			}
			else {
				argchange = 3;
				if (argcount <= argchange) { DBG_LOG("fdl <文件> <地址>\n"); argc -= argchange; argv += argchange; continue; }
				addr = strtoul(str2[3], NULL, 0);
			}

			if (fdl2_executed > 0) {
				DBG_LOG("FDL2已执行, 跳过\n");
				argc -= argchange; argv += argchange;
				continue;
			} else if (fdl1_loaded > 0) {
				if (fdl2_executed != -1)
				{
					fi = fopen(fn, "r");
					if (fi == NULL) { DBG_LOG("文件不存在。\n"); argc -= argchange; argv += argchange; continue; }
					else fclose(fi);
					send_file(io, fn, addr, end_data, blk_size ? blk_size : 528);
				}
			} else {
				if (fdl1_loaded != -1)
				{
					fi = fopen(fn, "r");
					if (fi == NULL) { DBG_LOG("文件不存在。\n"); argc -= argchange; argv += argchange; continue; }
					else fclose(fi);
					send_file(io, fn, addr, end_data, 528);
					if (exec_addr) {
						send_file(io, execfile, exec_addr, 0, 528);
						free(execfile);
					} else {
						encode_msg(io, BSL_CMD_EXEC_DATA, NULL, 0);
						if (send_and_check(io)) exit(1);
					}
				}
				else
				{
					encode_msg(io, BSL_CMD_EXEC_DATA, NULL, 0);
					if (send_and_check(io)) exit(1);
				}
				DBG_LOG("执行 FDL1\n");
				if (addr == 0x5500 || addr == 0x65000800)
				{
					highspeed = 1;
					if (!baudrate) baudrate = 921600;
				}

				/* FDL1 (chk = sum) */
				io->flags &= ~FLAGS_CRC16;

				encode_msg(io, BSL_CMD_CHECK_BAUD, NULL, 1);
				for (i = 0; ; i++) {
					send_msg(io);
					recv_msg(io);
					if (recv_type(io) == BSL_REP_VER) break;
					DBG_LOG("检查波特率 失败\n");
					if (i == 4) ERR_EXIT("检测到错误的命令或错误的模式，请按电源键和音量+键7-10秒重新启动手机。\n");
					usleep(500000);
				}
				DBG_LOG("检查波特率 FDL1\n");

				DBG_LOG("BSL_REP_VER: ");
				print_string(stderr, io->raw_buf + 4, READ16_BE(io->raw_buf + 2));
				if (!memcmp(io->raw_buf + 4, "SPRD4", 5)) fdl2_executed = -1;

#if FDL1_DUMP_MEM
				//read dump mem
				int pagecount = 0;
				char* pdump;
				char chdump;
				FILE* fdump;
				fdump = fopen("ddd.bin", "wb");
				encode_msg(io, BSL_CMD_CHECK_BAUD, NULL, 1);
				while (1) {
					send_msg(io);
					ret = recv_msg(io);
					if (!ret) ERR_EXIT("timeout reached\n");
					if (recv_type(io) == BSL_CMD_READ_END) break;
					pdump = (char*)(io->raw_buf + 4);
					for (i = 0; i < 512; i++)
					{
						chdump = *(pdump++);
						if (chdump == 0x7d)
						{
							if (*pdump == 0x5d || *pdump == 0x5e) chdump = *(pdump++) + 0x20;
						}
						fputc(chdump, fdump);
					}
					DBG_LOG("转储页数 %d\n", ++pagecount);
				}
				fclose(fdump);
				DBG_LOG("转储内存端\n");
				//end
#endif

				encode_msg(io, BSL_CMD_CONNECT, NULL, 0);
				if (send_and_check(io)) exit(1);
				DBG_LOG("连接到 FDL1\n");
#if !USE_LIBUSB
				if (baudrate)
				{
					uint8_t data[4];
					WRITE32_BE(data, baudrate);
					encode_msg(io, BSL_CMD_CHANGE_BAUD, data, 4);
					if (!send_and_check(io)) {
						DBG_LOG("改变波特率 FDL1 到 %d\n", baudrate);
						call_SetProperty(io->handle, 0, 100, (LPCVOID)&baudrate);
					}
				}
#endif
				if (keep_charge) {
					encode_msg(io, BSL_CMD_KEEP_CHARGE, NULL, 0);
					if (!send_and_check(io)) DBG_LOG("保持充电 FDL1\n");
				}
				fdl1_loaded = 1;
			}
			argc -= argchange; argv += argchange;

		} else if (!strcmp(str2[1], "exec")) {
			if (fdl2_executed > 0) {
				DBG_LOG("FDL2 已执行, 跳过\n");
				argc -= 1; argv += 1;
				continue;
			} else if (fdl1_loaded > 0) {
				memset(&Da_Info, 0, sizeof(Da_Info));
				encode_msg(io, BSL_CMD_EXEC_DATA, NULL, 0);
				send_msg(io);
				// Feature phones respond immediately,
				// but it may take a second for a smartphone to respond.
				ret = recv_msg_timeout(io, 15000);
				if (!ret) ERR_EXIT("timeout reached\n");
				ret = recv_type(io);
				// Is it always bullshit?
				if (ret == BSL_REP_INCOMPATIBLE_PARTITION)
					get_Da_Info(io);
				else if (ret != BSL_REP_ACK)
					ERR_EXIT("unexpected response (0x%04x)\n", ret);
				DBG_LOG("执行 FDL2\n");
				if (Da_Info.bDisableHDLC) {
					encode_msg(io, BSL_CMD_DISABLE_TRANSCODE, NULL, 0);
					if (!send_and_check(io)) {
						io->flags &= ~FLAGS_TRANSCODE;
						DBG_LOG("禁用转码\n");
					}
				}
				if (Da_Info.bSupportRawData == 2) {
					if (fdl2_executed) {
						Da_Info.bSupportRawData = 0;
						DBG_LOG("SPRD4中禁用WRITE_RAW_DATA\n");
					}
					else {
						encode_msg(io, BSL_CMD_WRITE_RAW_DATA_ENABLE, NULL, 0);
						if (!send_and_check(io)) DBG_LOG("禁用WRITE_RAW_DATA\n");
					}
					blk_size = 0xff00;
					ptable = partition_list(io, fn_partlist, &part_count);
				}
				else if (highspeed || Da_Info.dwStorageType == 0x103) {
					blk_size = 0xff00;
					ptable = partition_list(io, fn_partlist, &part_count);
				}
				else if (Da_Info.dwStorageType == 0x102) {
					ptable = partition_list(io, fn_partlist, &part_count);
				}
				else if (Da_Info.dwStorageType == 0x101) DBG_LOG("存储是nand\n");
				if (gpt_failed != 1) {
					if (selected_ab == 2) DBG_LOG("设备正在使用插槽b\n");
					else if (selected_ab == 1) DBG_LOG("设备正在使用插槽a\n");
					else DBG_LOG("设备未使用VAB\n");
				}
				if (nand_id == DEFAULT_NAND_ID) {
					nand_info[0] = (uint8_t)pow(2, nand_id & 3); //page size
					nand_info[1] = 32 / (uint8_t)pow(2, (nand_id >> 2) & 3); //spare area size
					nand_info[2] = 64 * (uint8_t)pow(2, (nand_id >> 4) & 3); //block size
				}
				fdl2_executed = 1;
			}
			argc -= 1; argv += 1;
#if !USE_LIBUSB
		} else if (!strcmp(str2[1], "baudrate")) {
			if (argcount > 2)
			{
				baudrate = strtoul(str2[2], NULL, 0);
				if (fdl2_executed) call_SetProperty(io->handle, 0, 100, (LPCVOID)&baudrate);
			}
			DBG_LOG("波特率是 %u\n", baudrate);
			argc -= 2; argv += 2;
#endif
		} else if (!strcmp(str2[1], "path")) {
			if (argcount > 2) strcpy(savepath, str2[2]);
			DBG_LOG("保存路径已设置为: %s\n", savepath);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "exec_addr")) {
			FILE* fi;
			if (0 == fdl1_loaded && argcount > 2) {
				exec_addr = strtoul(str2[2], NULL, 0);
				sprintf(execfile, "custom_exec_no_verify_%x.bin", exec_addr);
				fi = fopen(execfile, "r");
				if (fi == NULL) { DBG_LOG("%s 不存在\n", execfile); exec_addr = 0; }
				else fclose(fi);
			}
			DBG_LOG("当前的 exec_addr 是 0x%x\n", exec_addr);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "loadexec")) {
			const char* fn; char* ch; FILE* fi;
			if (argcount <= 2) { DBG_LOG("loadexec <文件>\n"); argc -= 2; argv += 2; continue; }
			if (0 == fdl1_loaded) {
				strcpy(execfile, str2[2]);

				if ((ch = strrchr(execfile, '/'))) fn = ch + 1;
				else if ((ch = strrchr(execfile, '\\'))) fn = ch + 1;
				else fn = execfile;
				char straddr[9] = { 0 };
				ret = sscanf(fn, "custom_exec_no_verify_%[0-9a-fA-F]", straddr);
				exec_addr = strtoul(straddr, NULL, 16);
				fi = fopen(execfile, "r");
				if (fi == NULL) { DBG_LOG("%s 不存在\n", execfile); exec_addr = 0; }
				else fclose(fi);
			}
			DBG_LOG("当前的 exec_addr 是 0x%x\n", exec_addr);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "nand_id")) {
			if (argcount > 2) {
				nand_id = strtol(str2[2], NULL, 0);
				nand_info[0] = (uint8_t)pow(2, nand_id & 3); //page size
				nand_info[1] = 32 / (uint8_t)pow(2, (nand_id >> 2) & 3); //spare area size
				nand_info[2] = 64 * (uint8_t)pow(2, (nand_id >> 4) & 3); //block size
			}
			DBG_LOG("当前的 nand_id 是 0x%x\n", nand_id);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "read_flash")) {
			const char *fn; uint64_t addr, offset, size;
			if (argcount <= 5) { DBG_LOG("错误的命令\n"); argc -= 5; argv += 5; continue; }

			addr = str_to_size(str2[2]);
			offset = str_to_size(str2[3]);
			size = str_to_size(str2[4]);
			fn = str2[5];
			if ((addr | size | offset | (addr + offset + size)) >> 32)
				{ DBG_LOG("已达到32位限制\n"); argc -= 5; argv += 5; continue; }
			dump_flash(io, addr, offset, size, fn,
					blk_size ? blk_size : 1024);
			argc -= 5; argv += 5;

		} else if (!strcmp(str2[1], "read_mem")) {
			const char *fn; uint64_t addr, size;
			if (argcount <= 4) { DBG_LOG("错误的命令\n"); argc -= 4; argv += 4; continue; }

			addr = str_to_size(str2[2]);
			size = str_to_size(str2[3]);
			fn = str2[4];
			if ((addr | size | (addr + size)) >> 32)
				{ DBG_LOG("已达到32位限制\n"); argc -= 4; argv += 4; continue; }
			dump_mem(io, addr, size, fn,
					blk_size ? blk_size : 1024);
			argc -= 4; argv += 4;

		} else if (!strcmp(str2[1], "part_size")) {
			const char *name;
			if (argcount <= 2) { DBG_LOG("错误的命令\n"); argc -= 2; argv += 2; continue; }

			name = str2[2];
			if (selected_ab < 0) select_ab(io);
			find_partition_size(io, name);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "p") || !strcmp(str2[1], "print")) {
			if (part_count) {
				DBG_LOG("  0 %36s     256KB\n", "splloader");
				for (i = 0; i < part_count; i++) {
					DBG_LOG("%3d %36s %7lldMB\n", i + 1, (*(ptable + i)).name, ((*(ptable + i)).size >> 20));
				}
			}
			argc -= 1; argv += 1;

		} else if (!strcmp(str2[1], "read_part")) {
			const char *name, *fn; uint64_t offset, size;
			uint64_t realsize = 0;
			char name_ab[36];
			int verbose = io->verbose;
			if (argcount <= 5) { DBG_LOG("read_part <分区名称> <偏移量> <大小> <文件路径>\n(读取nand上的ubi) read_part system 0 ubi40m system.bin\n"); argc -= 5; argv += 5; continue; }

			name = str2[2];
			if (selected_ab < 0) select_ab(io);
			io->verbose = 0;
			realsize = check_partition(io, name);
			if (!realsize) {
				if (selected_ab > 0) {
					snprintf(name_ab, sizeof(name_ab), "%s_%c", name, 96 + selected_ab);
					realsize = check_partition(io, name_ab);
					name = name_ab;
				}
				if (!realsize) {
					DBG_LOG("分区不存在\n");
					io->verbose = verbose;
					argc -= 5; argv += 5;
					continue;
				}
			}
			offset = str_to_size_ubi(str2[3], nand_info);
			size = str_to_size_ubi(str2[4], nand_info);
			if (0xffffffff == size) size = find_partition_size(io, name);
			fn = str2[5];
			if (offset + size < offset)
				{ DBG_LOG("已达到64位限制\n"); argc -= 5; argv += 5; continue; }
			io->verbose = verbose;
			dump_partition(io, name, offset, size, fn, blk_size ? blk_size : DEFAULT_BLK_SIZE);
			argc -= 5; argv += 5;

		} else if (!strcmp(str2[1], "r")) {
			uint64_t realsize = 0;
			const char* name = str2[2];
			char name_ab[36];
			if (argcount <= 2) { DBG_LOG("r all/all_lite/分区名称/分区id\n"); argc -= 2; argv += 2; continue; }
			if (!memcmp(name, "splloader", 9)) {
				realsize = 256 * 1024;
			}
			else if (isdigit(name[0])) {
				if (gpt_failed == 1) ptable = partition_list(io, fn_partlist, &part_count);
				i = atoi(name);
				if (i > part_count) { DBG_LOG("分区不存在\n"); argc -= 2; argv += 2; continue; }
				if (i == 0) {
					name = "splloader";
					realsize = 256 * 1024;
				}
				else {
					name = (*(ptable + i - 1)).name;
					realsize = (*(ptable + i - 1)).size;
				}
			}
			else if (!strcmp(name, "preset_modem")) {
				if (gpt_failed == 1) ptable = partition_list(io, fn_partlist, &part_count);
				if (!part_count) { DBG_LOG("分区表不可用\n"); argc -= 2; argv += 2; continue; }
				for (i = 0; i < part_count; i++)
					if (0 == strncmp("l_", (*(ptable + i)).name, 2) || 0 == strncmp("nr_", (*(ptable + i)).name, 3)) {
						char dfile[40];
						snprintf(dfile, sizeof(dfile), "%s.bin", (*(ptable + i)).name);
						dump_partition(io, (*(ptable + i)).name, 0, (*(ptable + i)).size, dfile, blk_size ? blk_size : DEFAULT_BLK_SIZE);
					}
				argc -= 2; argv += 2;
				continue;
			}
			else if (!strcmp(name, "all")) {
				if (gpt_failed == 1) ptable = partition_list(io, fn_partlist, &part_count);
				if (!part_count) { DBG_LOG("分区表不可用\n"); argc -= 2; argv += 2; continue; }
				dump_partition(io, "splloader", 0, 256 * 1024, "splloader.bin", blk_size ? blk_size : DEFAULT_BLK_SIZE);
				for (i = 0; i < part_count; i++)
				{
					char dfile[40];
					if (!memcmp((*(ptable + i)).name, "blackbox", 8)) continue;
					else if (!memcmp((*(ptable + i)).name, "cache", 5)) continue;
					else if (!memcmp((*(ptable + i)).name, "userdata", 8)) continue;
					snprintf(dfile, sizeof(dfile), "%s.bin", (*(ptable + i)).name);
					dump_partition(io, (*(ptable + i)).name, 0, (*(ptable + i)).size, dfile, blk_size ? blk_size : DEFAULT_BLK_SIZE);
				}
				argc -= 2; argv += 2;
				continue;
			}
			else if (!strcmp(name, "all_lite")) {
				if (gpt_failed == 1) ptable = partition_list(io, fn_partlist, &part_count);
				if (!part_count) { DBG_LOG("分区表不可用\n"); argc -= 2; argv += 2; continue; }
				dump_partition(io, "splloader", 0, 256 * 1024, "splloader.bin", blk_size ? blk_size : DEFAULT_BLK_SIZE);
				for (i = 0; i < part_count; i++)
				{
					char dfile[40];
					size_t namelen = strlen((*(ptable + i)).name);
					if (!memcmp((*(ptable + i)).name, "blackbox", 8)) continue;
					else if (!memcmp((*(ptable + i)).name, "cache", 5)) continue;
					else if (!memcmp((*(ptable + i)).name, "userdata", 8)) continue;
					if (selected_ab == 1 && namelen > 2 && 0 == strcmp((*(ptable + i)).name + namelen - 2, "_b")) continue;
					snprintf(dfile, sizeof(dfile), "%s.bin", (*(ptable + i)).name);
					dump_partition(io, (*(ptable + i)).name, 0, (*(ptable + i)).size, dfile, blk_size ? blk_size : DEFAULT_BLK_SIZE);
				}
				if (selected_ab == 2) DBG_LOG("当设备位于插槽B中时，插槽A中的一些分区仍在使用中；因此，所有分区都被转储。\n");
				argc -= 2; argv += 2;
				continue;
			}
			else if (part_count) {
				if (selected_ab > 0) snprintf(name_ab, sizeof(name_ab), "%s_%c", name, 96 + selected_ab);
				for (i = 0; i < part_count; i++) {
					if (!strcmp(name, (*(ptable + i)).name)) {
						realsize = (*(ptable + i)).size;
						break;
					}
					if (selected_ab > 0 && !strcmp(name_ab, (*(ptable + i)).name)) {
						realsize = (*(ptable + i)).size;
						name = name_ab;
						break;
					}
				}
				if (i == part_count) { DBG_LOG("分区不存在\n"); argc -= 2; argv += 2; continue; }
			}
			else
			{
				if (selected_ab < 0) select_ab(io);
				realsize = check_partition(io, name);
				if (!realsize) {
					if (selected_ab > 0) {
						snprintf(name_ab, sizeof(name_ab), "%s_%c", name, 96 + selected_ab);
						realsize = check_partition(io, name_ab);
						name = name_ab;
					}
					if (!realsize) {
						DBG_LOG("分区不存在\n");
						argc -= 2; argv += 2;
						continue;
					}
				}
				realsize = find_partition_size(io, name);
			}
			char dfile[40];
			if (isdigit(str2[2][0])) snprintf(dfile, sizeof(dfile), "%s.bin", name);
			else snprintf(dfile, sizeof(dfile), "%s.bin", str2[2]);
			dump_partition(io, name, 0, realsize, dfile, blk_size ? blk_size : DEFAULT_BLK_SIZE);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "read_parts")) {
			const char* fn; FILE* fi;
			if (argcount <= 2) { DBG_LOG("read_parts <分区表文件>\n"); argc -= 2; argv += 2; continue; }
			fn = str2[2];
			fi = fopen(fn, "r");
			if (fi == NULL) { DBG_LOG("文件不存在\n"); argc -= 2; argv += 2; continue; }
			else fclose(fi);
			dump_partitions(io, fn, nand_info, blk_size ? blk_size : DEFAULT_BLK_SIZE);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "partition_list")) {
			if (argcount <= 2) { DBG_LOG("partition_list <分区表保存路径>\n"); argc -= 2; argv += 2; continue; }
			if (gpt_failed < 1) { DBG_LOG("partition_list 不应运行两次\n"); argc -= 2; argv += 2; continue; }
			ptable = partition_list(io, str2[2], &part_count);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "repartition")) {
			const char *fn;FILE *fi;
			if (argcount <= 2) { DBG_LOG("repartition <xml分区表文件>\n"); argc -= 2; argv += 2; continue; }
			fn = str2[2];
			fi = fopen(fn, "r");
			if (fi == NULL) { DBG_LOG("文件不存在\n"); argc -= 2; argv += 2; continue; }
			else fclose(fi);
			if (skip_confirm) repartition(io, str2[2]);
			else if (check_confirm("repartition")) repartition(io, str2[2]);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "erase_part") || !strcmp(str2[1], "e")) {
			uint64_t realsize = 0;
			const char* name = str2[2];
			char name_ab[36];
			int verbose = io->verbose;
			if (argcount <= 2) { DBG_LOG("erase_part 分区名称/分区id\n"); argc -= 2; argv += 2; continue; }
			if (selected_ab < 0) select_ab(io);
			i = -1;
			if (isdigit(name[0])) {
				if (part_count) i = atoi(name);
				else { DBG_LOG("gpt表为空\n"); argc -= 2; argv += 2; continue; }
				if (i > part_count) { DBG_LOG("分区不存在\n"); argc -= 2; argv += 2; continue; }
			}
			if (!skip_confirm)
				if (!check_confirm("erase partition"))
				{
					argc -= 2; argv += 2;
					continue;
				}
			if (i == 0) erase_partition(io, "splloader");
			else if (i > 0) erase_partition(io, (*(ptable + i - 1)).name);
			else {
				io->verbose = 0;
				realsize = check_partition(io, name);
				if (!realsize) {
					if (selected_ab > 0) {
						snprintf(name_ab, sizeof(name_ab), "%s_%c", name, 96 + selected_ab);
						realsize = check_partition(io, name_ab);
						name = name_ab;
					}
					if (!realsize) {
						DBG_LOG("分区不存在\n");
						io->verbose = verbose;
						argc -= 2; argv += 2;
						continue;
					}
				}
				io->verbose = verbose;
				erase_partition(io, name);
			}
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "write_part") || !strcmp(str2[1], "w")) {
			const char *fn;FILE *fi;
			uint64_t realsize = 0;
			const char* name = str2[2];
			char name_ab[36];
			int verbose = io->verbose;
			if (argcount <= 3) { DBG_LOG("write_part 分区名称/分区id <文件>\n"); argc -= 3; argv += 3; continue; }
			fn = str2[3];
			fi = fopen(fn, "r");
			if (fi == NULL) { DBG_LOG("文件不存在\n"); argc -= 3; argv += 3; continue; }
			else fclose(fi);
			if (selected_ab < 0) select_ab(io);
			i = -1;
			if (isdigit(name[0])) {
				if (part_count) i = atoi(name);
				else { DBG_LOG("gpt表为空\n"); argc -= 3; argv += 3; continue; }
				if (i > part_count) { DBG_LOG("分区不存在\n"); argc -= 3; argv += 3; continue; }
			}
			if (!skip_confirm)
				if (!check_confirm("write partition"))
				{
					argc -= 3; argv += 3;
					continue;
				}
			if (i == 0) load_partition(io, "splloader", str2[3], 4096);
			else if (i > 0) {
				if (strstr((*(ptable + i)).name, "fixnv1")) load_nv_partition(io, (*(ptable + i)).name, str2[3], 4096);
				else load_partition(io, (*(ptable + i)).name, str2[3], blk_size ? blk_size : DEFAULT_BLK_SIZE);
			}
			else {
				io->verbose = 0;
				realsize = check_partition(io, name);
				if (!realsize) {
					if (selected_ab > 0) {
						snprintf(name_ab, sizeof(name_ab), "%s_%c", name, 96 + selected_ab);
						realsize = check_partition(io, name_ab);
						name = name_ab;
					}
					if (!realsize) {
						DBG_LOG("分区不存在\n");
						io->verbose = verbose;
						argc -= 3; argv += 3;
						continue;
					}
				}
				io->verbose = verbose;
				if (strstr(name, "fixnv1")) load_nv_partition(io, name, str2[3], 4096);
				else load_partition(io, name, str2[3], blk_size ? blk_size : DEFAULT_BLK_SIZE);
			}
			argc -= 3; argv += 3;

		} else if (!strcmp(str2[1], "write_parts")) {
			if (argcount <= 2) { DBG_LOG("write_parts <保存路径>\n"); argc -= 2; argv += 2; continue; }
			if (skip_confirm) load_partitions(io, str2[2], blk_size ? blk_size : DEFAULT_BLK_SIZE);
			else if (check_confirm("write all partitions")) load_partitions(io, str2[2], blk_size ? blk_size : DEFAULT_BLK_SIZE);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "read_pactime")) {
			read_pactime(io);
			argc -= 1; argv += 1;

		} else if (!strcmp(str2[1], "blk_size") || !strcmp(str2[1], "bs")) {
			if (argcount <= 2) { DBG_LOG("blk_size <byte>\n\t最大65535\n"); argc -= 2; argv += 2; continue; }
			blk_size = strtol(str2[2], NULL, 0);
			blk_size = blk_size < 0 ? 0 :
					blk_size > 0xffff ? 0xffff : blk_size;
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "fblk_size") || !strcmp(str2[1], "fbs")) {
			if (argcount <= 2) { DBG_LOG("fblk_size mb\n"); argc -= 2; argv += 2; continue; }
			fblk_size = strtoull(str2[2], NULL, 0) * 1024 * 1024;
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "verity")) {
			if (argcount <= 2) { DBG_LOG("verity {0,1}\n"); argc -= 2; argv += 2; continue; }
			if (atoi(str2[2])) dm_enable(io, blk_size ? blk_size : DEFAULT_BLK_SIZE);
			else
			{
				DBG_LOG("警告：禁用dm-verity需要禁用写入验证FDL2\n");
				if (!skip_confirm)
					if (!check_confirm("disable dm-verity"))
					{
						argc -= 2; argv += 2;
						continue;
					}
				dm_disable(io, blk_size ? blk_size : DEFAULT_BLK_SIZE);
			}
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "skip_confirm")) {
			if (argcount <= 2) { DBG_LOG("skip_confirm {0,1}\n"); argc -= 2; argv += 2; continue; }
			skip_confirm = atoi(str2[2]);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "rawdata")) {
			if (argcount <= 2) { DBG_LOG("rawdata {0,1,2}\n"); argc -= 2; argv += 2; continue; }
			Da_Info.bSupportRawData = atoi(str2[2]);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "chip_uid")) {
			encode_msg(io, BSL_CMD_READ_CHIP_UID, NULL, 0);
			send_msg(io);
			ret = recv_msg(io);
			if (!ret) ERR_EXIT("timeout reached\n");
			if ((ret = recv_type(io)) != BSL_REP_READ_CHIP_UID)
				{ DBG_LOG("意外响应 (0x%04x)\n", ret); argc -= 1; argv += 1; continue; }

			DBG_LOG("BSL_REP_READ_CHIP_UID: ");
			print_string(stderr, io->raw_buf + 4, READ16_BE(io->raw_buf + 2));
			argc -= 1; argv += 1;

		} else if (!strcmp(str2[1], "disable_transcode")) {
			encode_msg(io, BSL_CMD_DISABLE_TRANSCODE, NULL, 0);
			if (!send_and_check(io)) io->flags &= ~FLAGS_TRANSCODE;
			argc -= 1; argv += 1;

		} else if (!strcmp(str2[1], "transcode")) {
			unsigned a, f;
			if (argcount <= 2) { DBG_LOG("错误的指令\n"); argc -= 2; argv += 2; continue; }
			a = atoi(str2[2]);
			if (a >> 1) { DBG_LOG("错误的指令\n"); argc -= 2; argv += 2; continue; }
			f = (io->flags & ~FLAGS_TRANSCODE);
			io->flags = f | (a ? FLAGS_TRANSCODE : 0);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "keep_charge")) {
			if (argcount <= 2) { DBG_LOG("keep_charge {0,1}\n"); argc -= 2; argv += 2; continue; }
			keep_charge = atoi(str2[2]);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "timeout")) {
			if (argcount <= 2) { DBG_LOG("timeout <毫秒>\n"); argc -= 2; argv += 2; continue; }
			io->timeout = atoi(str2[2]);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "end_data")) {
			if (argcount <= 2) { DBG_LOG("end_data {0,1}\n"); argc -= 2; argv += 2; continue; }
			end_data = atoi(str2[2]);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "reset")) {
			if (!fdl1_loaded) {
				DBG_LOG("FDL未就绪\n");
				argc -= 1; argv += 1;
				continue;
			}
			encode_msg(io, BSL_CMD_NORMAL_RESET, NULL, 0);
			if (!send_and_check(io)) break;

		} else if (!strcmp(str2[1], "poweroff")) {
			if (!fdl1_loaded) {
				DBG_LOG("FDL未就绪\n");
				argc -= 1; argv += 1;
				continue;
			}
			encode_msg(io, BSL_CMD_POWER_OFF, NULL, 0);
			if (!send_and_check(io)) break;

		} else if (!strcmp(str2[1], "verbose")) {
			if (argcount <= 2) { DBG_LOG("verbose {0,1,2}\n"); argc -= 2; argv += 2; continue; }
			io->verbose = atoi(str2[2]);
			argc -= 2; argv += 2;

		} else if (strlen(str2[1])) {
			print_help();
			argc = 1;
		}
		if (in_quote != -1)
			for (i = 1; i < argcount; i++)
				free(str2[i]);
		free(str2);
		if (m_bOpened == -1) {
			DBG_LOG("设备断开, 退出程序...\n");
			break;
		}
	}
	free(ptable);
	spdio_free(io);
	return 0;
}
