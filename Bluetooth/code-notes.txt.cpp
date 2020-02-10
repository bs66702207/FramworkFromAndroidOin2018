/**针对视频中的代码目录 windows + usb蓝牙模块*/

// F:\git-prj\FramworkFromAndroidOin2018\Bluetooth\btstack-master_v2\port\windows-winusb\main.c
int main(int argc, const char * argv[]){
    ...
	btstack_run_loop_init(btstack_run_loop_windows_get_instance());//操作系统相关代码
	...
    // setup USB Transport
    transport = hci_transport_usb_instance();//硬件相关的代码，以后就啊hi用transport和硬件进行收发数据，具体描述可以见word

}

// F:\git-prj\FramworkFromAndroidOin2018\Bluetooth\btstack-master_v2\platform\windows\hci_transport_h2_winusb.c
// get usb singleton
static const hci_transport_t hci_transport_usb = {
    /* const char * name; */                                        "H2_WINUSB",
    /* void   (*init) (const void *transport_config); */            &usb_init,
    /* int    (*open)(void); */                                     &usb_open,
    /* int    (*close)(void); */                                    &usb_close,
    /* void   (*register_packet_handler)(void (*handler)(...); */   &usb_register_packet_handler,
    /* int    (*can_send_packet_now)(uint8_t packet_type); */       &usb_can_send_packet_now,
    /* int    (*send_packet)(...); */                               &usb_send_packet,
    /* int    (*set_baudrate)(uint32_t baudrate); */                NULL,
    /* void   (*reset_link)(void); */                               NULL,
#ifdef ENABLE_SCO_OVER_HCI
    /* void   (*set_sco_config)(uint16_t voice_setting, int num_connections); */ usb_set_sco_config, 
#else
    /* void   (*set_sco_config)(uint16_t voice_setting, int num_connections); */ NULL, 
#endif    
};

const hci_transport_t * hci_transport_usb_instance(void) {
    return &hci_transport_usb;
}

// F:\git-prj\FramworkFromAndroidOin2018\Bluetooth\btstack-master_v2\platform\btstack_run_loop_windows.c
static const btstack_run_loop_t btstack_run_loop_windows = {
    &btstack_run_loop_windows_init,
    &btstack_run_loop_windows_add_data_source,
    &btstack_run_loop_windows_remove_data_source,
    &btstack_run_loop_windows_enable_data_source_callbacks,
    &btstack_run_loop_windows_disable_data_source_callbacks,
    &btstack_run_loop_windows_set_timer,
    &btstack_run_loop_windows_add_timer,
    &btstack_run_loop_windows_remove_timer,
    &btstack_run_loop_windows_execute,//很重要，它是一个循环，在循环中等待、读取、处理函数
    &btstack_run_loop_windows_dump_timer,
    &btstack_run_loop_windows_get_time_ms,
};

/**
 * Provide btstack_run_loop_windows instance
 */
const btstack_run_loop_t * btstack_run_loop_windows_get_instance(void){
    return &btstack_run_loop_windows;
}


//btstack_data_source_t结构体
//F:\git-prj\FramworkFromAndroidOin2018\Bluetooth\btstack-master_v2\src\btstack_run_loop.h
typedef struct btstack_data_source {
	// linked item
    btstack_linked_item_t item;

    // item to watch in run loop
    union {
	    // file descriptor for posix systems
	    int  fd;//linux
    	// handle on windows
    	void * handle;	
    } source;

    // callback to call for enabled callback types
    void  (*process)(struct btstack_data_source *ds, btstack_data_source_callback_type_t callback_type);//数据处理的起点
/**
各个句柄对应的处理函数，是该句柄数据的处理起点，它将会调用上面各层提供的处理函数。这些处理函数，最终都会通过以下调用，把数据上报给各层，比如
usb_process_event_in
    -> packet_handler(HCI_EVENT_PACKET, hci_event_in_buffer, bytes_read);
在hci_transport_usb里面，由usb_register_packet_handler来注册packet_handler的具体函数，在哪调用register_packet_handler呢？
在~/src/hci.c
void hci_init(const hci_transport_t *transport, const void *config){
    transport->register_packet_handler(&c);
}
*/

    // flags storing enabled callback types
    uint16_t flags;

} btstack_data_source_t;


//所以，我们从fd拿到数据后，调用顺序process->packet_handler(由hci.c来注册指定是哪一个具体的packet_handler)
static void packet_handler(uint8_t packet_type, uint8_t *packet, uint16_t size){
    hci_dump_packet(packet_type, 1, packet, size);
    switch (packet_type) {
        case HCI_EVENT_PACKET:
            event_handler(packet, size);
			/**
			->hci_emit_event
			*/
            break;
        case HCI_ACL_DATA_PACKET:
            acl_handler(packet, size);
            break;
#ifdef ENABLE_CLASSIC
        case HCI_SCO_DATA_PACKET:
            sco_handler(packet, size);
            break;
#endif
        default:
            break;
    }
}
static void hci_emit_event(uint8_t * event, uint16_t size, int dump){
    // dump packet
    if (dump) {
        hci_dump_packet( HCI_EVENT_PACKET, 0, event, size);
    } 

    // dispatch to all event handlers
    btstack_linked_list_iterator_t it;
    btstack_linked_list_iterator_init(&it, &hci_stack->event_handlers);//从hci_back链表取出来
    while (btstack_linked_list_iterator_has_next(&it)){
        btstack_packet_callback_registration_t * entry = (btstack_packet_callback_registration_t*) btstack_linked_list_iterator_next(&it);
        entry->callback(HCI_EVENT_PACKET, 0, event, size);//调用callbacks，各层可以使用hci_add_event_handler来添加自己的callback
    }
}


5.谁触发了数据的传输？
之前我们说过主循环里在等待数据，只有我们给蓝牙模块发送命令之后，它才会回送数据。
那么，在哪里给蓝牙模块发送了第1个命令？在APP代码中，必有如下语句：
// turn on!
hci_power_control(HCI_POWER_ON);

这会导致给蓝牙模块发送一系列的初始化命令，
初始化成功后，APP通过hci_add_event_handler注册的函数就会被调用，在这个函数里就可以执行我们自己的代码，比如发起scan、发起connection等等。

回到main函数，初始化完成之后，
btstack_chipset_intel_download_firmware(hci_transport_usb_instance(), &intel_firmware_done);
->btstack_main(main_argc, main_argv);
->随便搜索个main，比如~/example/a2dp_sink_demo.c -> hci_power_control(HCI_POWER_ON);//以后所有数据都是在前面说的住循环里面来处理

第11节_BLE协议链路层(LL)_P44
1. 涉及打牌广播包，主设备发起连接请求，从设备响应连接请求，随机数是固定的
2. 通过数据包LLID位来确认是LL层处理的数据，还是需要LL层继续往上传递，L2CAP
3. 信道的自适应调频算法，通过取模运算，来找到可用的channel
