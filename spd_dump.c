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
		"˵��\n"
		"\tspd_dump [ѡ��] [ָ��] [�˳�ָ��]\n"
		"\n����\n"
		"\t����ģʽ\n"
		"\t\tspd_dump --wait 300 fdl /path/to/fdl1 fdl1_addr fdl /path/to/fdl2 fdl2_addr exec path savepath r all_lite reset\n"
		"\tInteractive mode\n"
		"\t\tspd_dump --wait 300 fdl /path/to/fdl1 fdl1_addr fdl /path/to/fdl2 fdl2_addr exec\n"
		"\t�ɹ���Ӧ��ʾ FDL2>\n"
		"\nѡ��\n"
		"\t--wait <����>\n"
		"\t\tָ���ȴ��豸���ӵ�ʱ�䡣\n"
		"\t--stage <����>|-r|--reconnect\n"
		"\t\t��������������brom/fdl1/fdl2�׶ε��豸�����������������ν������������Ҳ�У���\n"
		"\t\t(����brom/fdl1�׶ε��豸�������޴��������ӣ�����fdl2�׶�ֻ����������һ��)\n"
		"\t--verbose <�ȼ�>\n"
		"\t\t������Ļ��־����ϸ�̶ȣ�֧��0��1��2����Ӱ���ļ���־����\n"
		"\t--kick\n"
		"\t\tʹ�� boot_diag->cali_diag->dl_diag ;�������豸��\n"
		"\t--kickto <mode>\n"
		"\t\tʹ��boot_diag->custom_diag ;�������豸��֧�ֵ�ģʽΪ0-127��\n"
		"\t\t(ģʽ0Ϊums9621ƽ̨���°�--kickto 2, ģʽ 1 = cali_diag, ģʽ 2 = dl_diag; ���������豸��֧��ģʽ 2)\n"
		"\t-?|-h|--help\n"
		"\t\t��ʾʹ�ð�����\n"
		"\n����ʱ����\n"
		"\tverbose <�ȼ�>\n"
		"\t\t������Ļ��־����ϸ�̶ȣ�֧��0��1��2����Ӱ���ļ���־����\n"
		"\ttimeout <����>\n"
		"\t\t���ö�д�ȴ��ĳ�ʱʱ�䣨���룩\n"
		"\tbaudrate [������]\n\t\t(����Windows SPRD���������brom/fdl2�׶�)\n"
		"\t\t֧�ֵĲ�����Ϊ57600��115200��230400��460800��921600��1000000��2000000��3250000��4000000��\n"
		"\t\t��u-boot/littlekernelԴ�����У�ֻ�г���115200��230400��460800��921600��\n"
		"\texec_addr [addr]\n\t\t������brom�׶Σ�\n"
		"\t\t�� customexec_no_verify_addr.bin ���͵�ָ�����ڴ��ַ�����ƹ�brom�� splloader/fdl1 ��ǩ����֤��\n"
		"\t\t����CVE-2022-38694��\n"
		"\tfdl <�ļ�·��> <��ַ>\n"
		"\t\t���ļ���splloader,fdl1,fdl2,sml,trustos,teecfg�����͵�ָ�����ڴ��ַ��\n"
		"\tloadfdl <�ļ�·��>\n"
		"\t\t���ļ���splloader,fdl1,fdl2,sml,trustos,teecfg�����͵����ļ������ڴ��ַ,��:0x9efffe00.bin\n"
		"\texec\n"
		"\t\t��fdl1�׶�ִ���ѷ��͵��ļ���ͨ����sml��fdl2��Ҳ��Ϊuboot/lk��һ��ʹ�á�\n"
		"\tpath [����·��]\n"
		"\t\t����r,read_part(s),read_flash��read_mem����ı���Ŀ¼��\n"
		"\tnand_id [id]\n"
		"\t\tָ��nandоƬ��4th id�������ò���Ӱ��read_part(s)������С���㷨��Ĭ��ֵΪ0x15��\n"
		"\trawdata {0,2}\n\t\t������fdl2�׶Σ�\n"
		"\t\trawdataЭ�����ڼ���w��write_part�����rawdataΪ2ʱ��д���ٶ���blk_size�޹�\n"
		"\t\trawdataЭ�����ڼ���w��write_part�����rawdataΪ2ʱ��д���ٶ���blk_size�޹أ�������u-boot/lk�����Ĭ��2�Ŀ��Ը�0/2��Ĭ��0�Ĳ��ܸ�2��ע�⣺��ʱ��֧��Ĭ��rawdata=1���豸��\n"
		"\tblk_size <byte>\n\t\t������fdl2�׶Σ�\n"
		"\t\t���ÿ��С�����Ϊ65535�ֽڡ���ѡ�����ڼӿ�r��w��read_part(s)��write_part(s)������ٶȡ�\n"
		"\tr all|��������|����id\n"
		"\t\t�����������ʱ��\n"
		"\t\t\tr all: ȫ�̱��� (���� blackbox, cache, userdata)\n"
		"\t\t\tr all_lite: ȫ�̱��� (�ǻ��۷���, blackbox, cache, and userdata)\n"
		"\t\tW������������ʱ:\n"
		"\t\t\tr ���Զ����㲿����С��֧��emmc/ufs�ϵ����з�����NAND�Ͻ�֧��ubipac������\n"
		"\tread_part <��������|����id> <ƫ����> <��С> <����·��>\n"
		"\t\t�Ը�����ƫ�����ʹ�С���ض�������ȡ���ļ��С�\n"
		"\t\t����nand�϶�ȡubi��read_part system 0 ubi40m system.bin\n"
		"\tread_parts <�������ļ�>\n"
		"\t\t����XML���ͷ����б���豸��ȡ����������ļ����ԡ�ubi����ͷ����ʹ��NAND ID�����С��\n"
		"\tw|write_part ��������|����id <�ļ�·��>\n"
		"\t\t��ָ�����ļ�д�������\n"
		"\twrite_parts <�����ļ���·��>\n"
		"\t\tд��ָ���ļ����������ļ����豸������ͨ����read_parts�õ���\n"
		"\te|erase_part ��������|����id\n"
		"\t\t����ָ��������\n"
		"\tpartition_list <������·��>\n"
		"\t\t��ȡemmc/ufs�ϵķ����б���������fdl2��֧�ִ����\n"
		"\trepartition <xml�������ļ�>\n"
		"\t����XML���ͷ����б����·�����\n"
		"\tp|print\n"
		"\t\t��ӡ�����б�\n"
		"\tverity {0,1}\n"
		"\t\t��Android 10(+)�Ͻ��û�����dm-verity\n"
		"\n�˳�ָ��\n"
		"\t(һ����FDL2�׶ο��ÿ��ã�ֻ�к��µ�FDL1��֧��)\n"
		"\treset ����\n"
		"\tpoweroff �ػ������豸�Ͽ�usb��\n"
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
	SetConsoleOutputCP(936);
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
	if (!execfile) ERR_EXIT("�ڴ����ʧ��\n");

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
		ERR_EXIT("libusb_init ʧ��: %s\n", libusb_error_name(ret));
#else
	io->handle = createClass();
	call_Initialize(io->handle);
#endif
	DBG_LOG("spd_dump���İ�, �汾:dev_xxxx_xxx\n");
	DBG_LOG("�����ֿ�:https://github.com/hxzbaka/spd_dump_zh\n");
	DBG_LOG("ԭ��ֿ�:https://github.com/TomKing062/spreadtrum_flash\n");
	DBG_LOG("\n");
	sprintf(fn_partlist, "partition_%lld.xml", (long long)time(NULL));
	while (argc > 1) {
		if (!strcmp(argv[1], "--wait")) {
			if (argc <= 2) ERR_EXIT("�����ѡ��\n");
			wait = atoi(argv[2]) * REOPEN_FREQ;
			argc -= 2; argv += 2;
		} else if (!strcmp(argv[1], "--verbose")) {
			if (argc <= 2) ERR_EXIT("�����ѡ��\n");
			io->verbose = atoi(argv[2]);
			argc -= 2; argv += 2;
		} else if (!strcmp(argv[1], "--stage")) {
			if (argc <= 2) ERR_EXIT("�����ѡ��\n");
			stage = 99;
			argc -= 2; argv += 2;
		} else if (strstr(argv[1], "-r")) {
			if (argc <= 1) ERR_EXIT("�����ѡ��\n");
			stage = 99;
			argc -= 1; argv += 1;
		} else if (strstr(argv[1], "help") || strstr(argv[1], "-h") || strstr(argv[1], "-?")) {
			if (argc <= 1) ERR_EXIT("�����ѡ��\n");
			print_help();
			return 0;
#ifdef __ANDROID__
		} else if (!strcmp(argv[1], "--usb-fd")) { // Termux spec
			if (argc <= 2) ERR_EXIT("�����ѡ��\n");
			xfd = atoi(argv[argc - 1]);
			argc -= 2; argv += 1;
#endif
		} else if (!strcmp(argv[1], "--kick")) {
			if (argc <= 1) ERR_EXIT("�����ѡ��\n");
			at = 1;
			argc -= 1; argv += 1;
		} else if (!strcmp(argv[1], "--kickto")) {
			if (argc <= 2) ERR_EXIT("�����ѡ��\n");
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
	if (!libusb_has_capability(LIBUSB_CAP_HAS_HOTPLUG)) { DBG_LOG("��ƽ̨�ϲ�֧���Ȳ��\n"); bListenLibusb = 0; bootmode = -1; at = 0; }
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
	DBG_LOG("����ת��Termux�����usb�˿�fd\n");
	// handle
	if (xfd < 0)
		ERR_EXIT("����: termux-usb -e \"./spd_dump --usb-fd\" /dev/bus/usb/xxx/xxx\n"
			"run on android need provide --usb-fd\n");

	if (libusb_wrap_sys_device(NULL, (intptr_t)xfd, &io->dev_handle))
		ERR_EXIT("libusb_wrap_sys_device �������˳���\n");

	device = libusb_get_device(io->dev_handle);
	if (libusb_get_device_descriptor(device, &desc))
		ERR_EXIT("libusb_get_device �������˳���");

	DBG_LOG("Vendor ID: %04x\nProduct ID: %04x\n", desc.idVendor, desc.idProduct);
	if (desc.idVendor != 0x1782 || desc.idProduct != 0x4d00) {
		ERR_EXIT("spec�豸���ܲ���spd�豸��\n");
	}
	call_Initialize_libusb(io);
#else
	if (!m_bOpened) DBG_LOG("���ڵȴ�dl_diag���� (%ds)\n", wait / REOPEN_FREQ);
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
			ERR_EXIT("libusb_open_device ʧ��\n");
#else
		if (io->verbose) DBG_LOG("CurTime: %.1f, CurPort: %d\n", (float)i / REOPEN_FREQ, curPort);
		if (curPort) break;
		if (i >= wait)
			ERR_EXIT("���Ҷ˿�ʧ��\n");
#endif
		usleep(1000000 / REOPEN_FREQ);
	}
#if USE_LIBUSB
	if (!m_bOpened)
	{
		if (libusb_open(curPort, &io->dev_handle) >= 0) call_Initialize_libusb(io);
		else ERR_EXIT("����ʧ��\n");
	}
#else
	if (!m_bOpened) if (!call_ConnectChannel(io->handle, curPort)) ERR_EXIT("����ʧ��\n");
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
					DBG_LOG("��鲨���� FDL1\n");
					if (!memcmp(io->raw_buf + 4, "SPRD4", 5)) fdl2_executed = -1;
				}
				else
				{
					DBG_LOG("��鲨���� bootrom\n");
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
				DBG_LOG("���ӵ� FDL1\n");
				if (keep_charge) {
					encode_msg(io, BSL_CMD_KEEP_CHARGE, NULL, 0);
					if (!send_and_check(io)) DBG_LOG("���ֳ�� FDL1\n");
				}
			}
			else DBG_LOG("���ӵ� bootrom\n");
			break;
		}
		else if (ret == BSL_REP_UNSUPPORTED_COMMAND)
		{
			encode_msg(io, BSL_CMD_DISABLE_TRANSCODE, NULL, 0);
			if (!send_and_check(io)) {
				io->flags &= ~FLAGS_TRANSCODE;
				DBG_LOG("����ת��\n");
			}
			fdl2_executed = 1;
			break;
		}
		else if (i == 4)
		{
			if (stage != -1) ERR_EXIT("��⵽��������������ģʽ���밴��Դ��������+��7-10�����������ֻ���\n");
			else { encode_msg(io, BSL_CMD_CONNECT, NULL, 0); stage++; i = -1; }
		}
	}

	char** save_argv = NULL;
	while (1) {
		if (fdl1_loaded == -1) argc += 2;
		else if (fdl2_executed == -1) argc += 1;
		if (argc > 1)
		{
			str2 = (char**)malloc(argc * sizeof(char*));
			if (fdl1_loaded == -1) {
				save_argv = argv;
				str2[1] = "loadfdl";
				str2[2] = "0x0";
			}
			else if (fdl2_executed == -1) {
				if (!save_argv) save_argv = argv;
				str2[1] = "exec";
			}
			else {
				if (save_argv) { argv = save_argv; save_argv = NULL; }
				for (i = 1; i < argc; i++) str2[i] = argv[i];
			}
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
					if (!str2[argcount]) ERR_EXIT("ת��ʧ��\n");
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
			else ERR_EXIT("ת��ʧ��\n");
			argcount++;
		}

		if (!strcmp(str2[1], "sendloop")) {
			const char* fn; uint32_t addr = 0; FILE* fi;
			if (argcount <= 3) { DBG_LOG("sendloop <�ļ�> <��ַ>\n"); argc -= 3; argv += 3; continue; }

			fn = str2[2];
			fi = fopen(fn, "r");
			if (fi == NULL) { DBG_LOG("�ļ������ڡ�\n"); argc -= 3; argv += 3; continue; }
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
			if (argcount <= 3) { DBG_LOG("send <�ļ�> <��ַ>\n"); argc -= 3; argv += 3; continue; }

			fn = str2[2];
			fi = fopen(fn, "r");
			if (fi == NULL) { DBG_LOG("�ļ������ڡ�\n"); argc -= 3; argv += 3; continue; }
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
				if (argcount <= argchange) { DBG_LOG("loadfdl <�ļ�>\n"); argc -= argchange; argv += argchange; continue; }
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
				else DBG_LOG("\"0x\" ���������Ҳ�����\n");
			}
			else {
				argchange = 3;
				if (argcount <= argchange) { DBG_LOG("fdl <�ļ�> <��ַ>\n"); argc -= argchange; argv += argchange; continue; }
				addr = strtoul(str2[3], NULL, 0);
			}

			if (fdl2_executed > 0) {
				DBG_LOG("FDL2��ִ��, ����\n");
				argc -= argchange; argv += argchange;
				continue;
			} else if (fdl1_loaded > 0) {
				if (fdl2_executed != -1)
				{
					fi = fopen(fn, "r");
					if (fi == NULL) { DBG_LOG("�ļ������ڡ�\n"); argc -= argchange; argv += argchange; continue; }
					else fclose(fi);
					send_file(io, fn, addr, end_data, blk_size ? blk_size : 528);
				}
			} else {
				if (fdl1_loaded != -1)
				{
					fi = fopen(fn, "r");
					if (fi == NULL) { DBG_LOG("�ļ������ڡ�\n"); argc -= argchange; argv += argchange; continue; }
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
				DBG_LOG("ִ�� FDL1\n");
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
					DBG_LOG("��鲨���� ʧ��\n");
					if (i == 4) ERR_EXIT("��⵽��������������ģʽ���밴��Դ��������+��7-10�����������ֻ���\n");
					usleep(500000);
				}
				DBG_LOG("��鲨���� FDL1\n");

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
					if (!ret) ERR_EXIT("�ѳ�ʱ\n");
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
					DBG_LOG("ת��ҳ�� %d\n", ++pagecount);
				}
				fclose(fdump);
				DBG_LOG("ת���ڴ��\n");
				//end
#endif

				encode_msg(io, BSL_CMD_CONNECT, NULL, 0);
				if (send_and_check(io)) exit(1);
				DBG_LOG("���ӵ� FDL1\n");
#if !USE_LIBUSB
				if (baudrate)
				{
					uint8_t data[4];
					WRITE32_BE(data, baudrate);
					encode_msg(io, BSL_CMD_CHANGE_BAUD, data, 4);
					if (!send_and_check(io)) {
						DBG_LOG("�ı䲨���� FDL1 �� %d\n", baudrate);
						call_SetProperty(io->handle, 0, 100, (LPCVOID)&baudrate);
					}
				}
#endif
				if (keep_charge) {
					encode_msg(io, BSL_CMD_KEEP_CHARGE, NULL, 0);
					if (!send_and_check(io)) DBG_LOG("���ֳ�� FDL1\n");
				}
				fdl1_loaded = 1;
			}
			argc -= argchange; argv += argchange;

		} else if (!strcmp(str2[1], "exec")) {
			if (fdl2_executed > 0) {
				DBG_LOG("FDL2 ��ִ��, ����\n");
				argc -= 1; argv += 1;
				continue;
			} else if (fdl1_loaded > 0) {
				memset(&Da_Info, 0, sizeof(Da_Info));
				encode_msg(io, BSL_CMD_EXEC_DATA, NULL, 0);
				send_msg(io);
				// Feature phones respond immediately,
				// but it may take a second for a smartphone to respond.
				ret = recv_msg_timeout(io, 15000);
				if (!ret) ERR_EXIT("�ѳ�ʱ\n");
				ret = recv_type(io);
				// Is it always bullshit?
				if (ret == BSL_REP_INCOMPATIBLE_PARTITION)
					get_Da_Info(io);
				else if (ret != BSL_REP_ACK)
					ERR_EXIT("������Ӧ (0x%04x)\n", ret);
				DBG_LOG("ִ�� FDL2\n");
				if (Da_Info.bDisableHDLC) {
					encode_msg(io, BSL_CMD_DISABLE_TRANSCODE, NULL, 0);
					if (!send_and_check(io)) {
						io->flags &= ~FLAGS_TRANSCODE;
						DBG_LOG("����ת��\n");
					}
				}
				if (Da_Info.bSupportRawData == 2) {
					if (fdl2_executed) {
						Da_Info.bSupportRawData = 0;
						DBG_LOG("SPRD4�н���WRITE_RAW_DATA\n");
					}
					else {
						encode_msg(io, BSL_CMD_WRITE_RAW_DATA_ENABLE, NULL, 0);
						if (!send_and_check(io)) DBG_LOG("����WRITE_RAW_DATA\n");
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
				else if (Da_Info.dwStorageType == 0x101) DBG_LOG("�洢��nand\n");
				if (gpt_failed != 1) {
					if (selected_ab == 2) DBG_LOG("�豸����ʹ�ò��b\n");
					else if (selected_ab == 1) DBG_LOG("�豸����ʹ�ò��a\n");
					else DBG_LOG("�豸δʹ��VAB\n");
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
			DBG_LOG("�������� %u\n", baudrate);
			argc -= 2; argv += 2;
#endif
		} else if (!strcmp(str2[1], "path")) {
			if (argcount > 2) strcpy(savepath, str2[2]);
			DBG_LOG("����·��������Ϊ: %s\n", savepath);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "exec_addr")) {
			FILE* fi;
			if (0 == fdl1_loaded && argcount > 2) {
				exec_addr = strtoul(str2[2], NULL, 0);
				sprintf(execfile, "custom_exec_no_verify_%x.bin", exec_addr);
				fi = fopen(execfile, "r");
				if (fi == NULL) { DBG_LOG("%s ������\n", execfile); exec_addr = 0; }
				else fclose(fi);
			}
			DBG_LOG("��ǰ�� exec_addr �� 0x%x\n", exec_addr);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "loadexec")) {
			const char* fn; char* ch; FILE* fi;
			if (argcount <= 2) { DBG_LOG("loadexec <�ļ�>\n"); argc -= 2; argv += 2; continue; }
			if (0 == fdl1_loaded) {
				strcpy(execfile, str2[2]);

				if ((ch = strrchr(execfile, '/'))) fn = ch + 1;
				else if ((ch = strrchr(execfile, '\\'))) fn = ch + 1;
				else fn = execfile;
				char straddr[9] = { 0 };
				ret = sscanf(fn, "custom_exec_no_verify_%[0-9a-fA-F]", straddr);
				exec_addr = strtoul(straddr, NULL, 16);
				fi = fopen(execfile, "r");
				if (fi == NULL) { DBG_LOG("%s ������\n", execfile); exec_addr = 0; }
				else fclose(fi);
			}
			DBG_LOG("��ǰ�� exec_addr �� 0x%x\n", exec_addr);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "nand_id")) {
			if (argcount > 2) {
				nand_id = strtol(str2[2], NULL, 0);
				nand_info[0] = (uint8_t)pow(2, nand_id & 3); //page size
				nand_info[1] = 32 / (uint8_t)pow(2, (nand_id >> 2) & 3); //spare area size
				nand_info[2] = 64 * (uint8_t)pow(2, (nand_id >> 4) & 3); //block size
			}
			DBG_LOG("��ǰ�� nand_id �� 0x%x\n", nand_id);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "read_flash")) {
			const char *fn; uint64_t addr, offset, size;
			if (argcount <= 5) { DBG_LOG("���������\n"); argc -= 5; argv += 5; continue; }

			addr = str_to_size(str2[2]);
			offset = str_to_size(str2[3]);
			size = str_to_size(str2[4]);
			fn = str2[5];
			if ((addr | size | offset | (addr + offset + size)) >> 32)
				{ DBG_LOG("�Ѵﵽ32λ����\n"); argc -= 5; argv += 5; continue; }
			dump_flash(io, addr, offset, size, fn,
					blk_size ? blk_size : 1024);
			argc -= 5; argv += 5;

		} else if (!strcmp(str2[1], "read_mem")) {
			const char *fn; uint64_t addr, size;
			if (argcount <= 4) { DBG_LOG("���������\n"); argc -= 4; argv += 4; continue; }

			addr = str_to_size(str2[2]);
			size = str_to_size(str2[3]);
			fn = str2[4];
			if ((addr | size | (addr + size)) >> 32)
				{ DBG_LOG("�Ѵﵽ32λ����\n"); argc -= 4; argv += 4; continue; }
			dump_mem(io, addr, size, fn,
					blk_size ? blk_size : 1024);
			argc -= 4; argv += 4;

		} else if (!strcmp(str2[1], "part_size")) {
			const char *name;
			if (argcount <= 2) { DBG_LOG("���������\n"); argc -= 2; argv += 2; continue; }

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
			if (argcount <= 5) { DBG_LOG("read_part <��������> <ƫ����> <��С> <�ļ�·��>\n(��ȡnand�ϵ�ubi) read_part system 0 ubi40m system.bin\n"); argc -= 5; argv += 5; continue; }

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
					DBG_LOG("����������\n");
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
				{ DBG_LOG("�Ѵﵽ64λ����\n"); argc -= 5; argv += 5; continue; }
			io->verbose = verbose;
			dump_partition(io, name, offset, size, fn, blk_size ? blk_size : DEFAULT_BLK_SIZE);
			argc -= 5; argv += 5;

		} else if (!strcmp(str2[1], "r")) {
			uint64_t realsize = 0;
			const char* name = str2[2];
			char name_ab[36];
			if (argcount <= 2) { DBG_LOG("r all/all_lite/��������/����id\n"); argc -= 2; argv += 2; continue; }
			if (!memcmp(name, "splloader", 9)) {
				realsize = 256 * 1024;
			}
			else if (isdigit(name[0])) {
				if (gpt_failed == 1) ptable = partition_list(io, fn_partlist, &part_count);
				i = atoi(name);
				if (i > part_count) { DBG_LOG("����������\n"); argc -= 2; argv += 2; continue; }
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
				if (!part_count) { DBG_LOG("����������\n"); argc -= 2; argv += 2; continue; }
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
				if (!part_count) { DBG_LOG("����������\n"); argc -= 2; argv += 2; continue; }
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
				if (!part_count) { DBG_LOG("����������\n"); argc -= 2; argv += 2; continue; }
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
				if (selected_ab == 2) DBG_LOG("���豸λ�ڲ��B��ʱ�����A�е�һЩ��������ʹ���У���ˣ����з�������ת����\n");
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
				if (i == part_count) { DBG_LOG("����������\n"); argc -= 2; argv += 2; continue; }
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
						DBG_LOG("����������\n");
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
			if (argcount <= 2) { DBG_LOG("read_parts <�������ļ�>\n"); argc -= 2; argv += 2; continue; }
			fn = str2[2];
			fi = fopen(fn, "r");
			if (fi == NULL) { DBG_LOG("�ļ�������\n"); argc -= 2; argv += 2; continue; }
			else fclose(fi);
			dump_partitions(io, fn, nand_info, blk_size ? blk_size : DEFAULT_BLK_SIZE);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "partition_list")) {
			if (argcount <= 2) { DBG_LOG("partition_list <��������·��>\n"); argc -= 2; argv += 2; continue; }
			if (gpt_failed < 1) { DBG_LOG("partition_list ��Ӧ��������\n"); argc -= 2; argv += 2; continue; }
			ptable = partition_list(io, str2[2], &part_count);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "repartition")) {
			const char *fn;FILE *fi;
			if (argcount <= 2) { DBG_LOG("repartition <xml�������ļ�>\n"); argc -= 2; argv += 2; continue; }
			fn = str2[2];
			fi = fopen(fn, "r");
			if (fi == NULL) { DBG_LOG("�ļ�������\n"); argc -= 2; argv += 2; continue; }
			else fclose(fi);
			if (skip_confirm) repartition(io, str2[2]);
			else if (check_confirm("repartition")) repartition(io, str2[2]);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "erase_part") || !strcmp(str2[1], "e")) {
			uint64_t realsize = 0;
			const char* name = str2[2];
			char name_ab[36];
			int verbose = io->verbose;
			if (argcount <= 2) { DBG_LOG("erase_part ��������/����id\n"); argc -= 2; argv += 2; continue; }
			if (selected_ab < 0) select_ab(io);
			i = -1;
			if (isdigit(name[0])) {
				if (part_count) i = atoi(name);
				else { DBG_LOG("gpt��Ϊ��\n"); argc -= 2; argv += 2; continue; }
				if (i > part_count) { DBG_LOG("����������\n"); argc -= 2; argv += 2; continue; }
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
						DBG_LOG("����������\n");
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
			if (argcount <= 3) { DBG_LOG("write_part ��������/����id <�ļ�>\n"); argc -= 3; argv += 3; continue; }
			fn = str2[3];
			fi = fopen(fn, "r");
			if (fi == NULL) { DBG_LOG("�ļ�������\n"); argc -= 3; argv += 3; continue; }
			else fclose(fi);
			if (selected_ab < 0) select_ab(io);
			i = -1;
			if (isdigit(name[0])) {
				if (part_count) i = atoi(name);
				else { DBG_LOG("gpt��Ϊ��\n"); argc -= 3; argv += 3; continue; }
				if (i > part_count) { DBG_LOG("����������\n"); argc -= 3; argv += 3; continue; }
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
						DBG_LOG("����������\n");
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
			if (argcount <= 2) { DBG_LOG("write_parts <����·��>\n"); argc -= 2; argv += 2; continue; }
			if (skip_confirm) load_partitions(io, str2[2], blk_size ? blk_size : DEFAULT_BLK_SIZE);
			else if (check_confirm("write all partitions")) load_partitions(io, str2[2], blk_size ? blk_size : DEFAULT_BLK_SIZE);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "read_pactime")) {
			read_pactime(io);
			argc -= 1; argv += 1;

		} else if (!strcmp(str2[1], "blk_size") || !strcmp(str2[1], "bs")) {
			if (argcount <= 2) { DBG_LOG("blk_size <byte>\n\t���65535\n"); argc -= 2; argv += 2; continue; }
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
				DBG_LOG("���棺����dm-verity��Ҫ����д����֤FDL2\n");
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
			if (!ret) ERR_EXIT("�ѳ�ʱ\n");
			if ((ret = recv_type(io)) != BSL_REP_READ_CHIP_UID)
				{ DBG_LOG("������Ӧ (0x%04x)\n", ret); argc -= 1; argv += 1; continue; }

			DBG_LOG("BSL_REP_READ_CHIP_UID: ");
			print_string(stderr, io->raw_buf + 4, READ16_BE(io->raw_buf + 2));
			argc -= 1; argv += 1;

		} else if (!strcmp(str2[1], "disable_transcode")) {
			encode_msg(io, BSL_CMD_DISABLE_TRANSCODE, NULL, 0);
			if (!send_and_check(io)) io->flags &= ~FLAGS_TRANSCODE;
			argc -= 1; argv += 1;

		} else if (!strcmp(str2[1], "transcode")) {
			unsigned a, f;
			if (argcount <= 2) { DBG_LOG("�����ָ��\n"); argc -= 2; argv += 2; continue; }
			a = atoi(str2[2]);
			if (a >> 1) { DBG_LOG("�����ָ��\n"); argc -= 2; argv += 2; continue; }
			f = (io->flags & ~FLAGS_TRANSCODE);
			io->flags = f | (a ? FLAGS_TRANSCODE : 0);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "keep_charge")) {
			if (argcount <= 2) { DBG_LOG("keep_charge {0,1}\n"); argc -= 2; argv += 2; continue; }
			keep_charge = atoi(str2[2]);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "timeout")) {
			if (argcount <= 2) { DBG_LOG("timeout <����>\n"); argc -= 2; argv += 2; continue; }
			io->timeout = atoi(str2[2]);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "end_data")) {
			if (argcount <= 2) { DBG_LOG("end_data {0,1}\n"); argc -= 2; argv += 2; continue; }
			end_data = atoi(str2[2]);
			argc -= 2; argv += 2;

		} else if (!strcmp(str2[1], "reset")) {
			if (!fdl1_loaded) {
				DBG_LOG("FDLδ����\n");
				argc -= 1; argv += 1;
				continue;
			}
			encode_msg(io, BSL_CMD_NORMAL_RESET, NULL, 0);
			if (!send_and_check(io)) break;

		} else if (!strcmp(str2[1], "poweroff")) {
			if (!fdl1_loaded) {
				DBG_LOG("FDLδ����\n");
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
			DBG_LOG("�豸�Ͽ�, �˳�����...\n");
			break;
		}
	}
	free(ptable);
	spdio_free(io);
	return 0;
}
