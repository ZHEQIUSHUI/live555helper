#ifndef __H_RTSP_CLIENT_WARPPER__
#define __H_RTSP_CLIENT_WARPPER__

#if __cplusplus
extern "C"
{
#endif
    typedef void* rtsp_client_t;
    typedef void (*rtsp_client_callback_t)(const void *buff, int len, void *reserve);

    rtsp_client_t rtspcli_start(char *_url, rtsp_client_callback_t _cb, void *reserve);

    void rtspcli_stop(rtsp_client_t *rtspcli);

#if __cplusplus
}
#endif
#endif