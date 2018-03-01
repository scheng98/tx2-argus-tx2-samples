/*
 * Copyright (c) 2016-2017, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

/**
 * @file
 * <b>NVIDIA Multimedia API: Buffering & Transform/Composition/Blending API</b>
 *
 */

/**
 * @defgroup ee_nvbuffering_group NV HW Buffer Utility API
 *
 * NVIDIA buffering utility library for use by applications.
 * @{
 */

#ifndef _NVBUF_UTILS_H_
#define _NVBUF_UTILS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <errno.h>

/**
 * Defines maximum number of planes for video frame.
 */
#define MAX_NUM_PLANES 3

/**
 * Defines maximum number of input video frames can be used for composition.
 */
#define MAX_COMPOSITE_FRAME 16

/**
 * Defines Layout formats for NvBuffer video planes.
 */
typedef enum
{
  /** Pitch Layout. */
  NvBufferLayout_Pitch,
  /** BlockLinear Layout. */
  NvBufferLayout_BlockLinear,
} NvBufferLayout;

/**
 * Defines memory access flags for NvBuffer.
 */
typedef enum
{
  /** Memory read. */
  NvBufferMem_Read,
  /** Memory write. */
  NvBufferMem_Write,
  /** Memory read & write. */
  NvBufferMem_Read_Write,
} NvBufferMemFlags;

/**
 * Defines color formats for NvBuffer.
 */
typedef enum
{
  /** YUV420 multi-planar. */
  NvBufferColorFormat_YUV420,
  /** YUV420 multi-planar. */
  NvBufferColorFormat_YVU420,
  /** Y/CbCr 4:2:0 multi-planar. */
  NvBufferColorFormat_NV12,
  /** Y/CbCr 4:2:0 multi-planar. */
  NvBufferColorFormat_NV21,
  /** YUV 4:2:2 planar. */
  NvBufferColorFormat_UYVY,
  /** YUV 4:2:2 planar. */
  NvBufferColorFormat_VYUY,
  /** YUV 4:2:2 planar. */
  NvBufferColorFormat_YUYV,
  /** YUV 4:2:2 planar. */
  NvBufferColorFormat_YVYU,
  /** BGRA-8-8-8-8 planar. */
  NvBufferColorFormat_ABGR32,
  /** XRGB-8-8-8-8 planar. */
  NvBufferColorFormat_XRGB32,
  /** ARGB-8-8-8-8 planar. */
  NvBufferColorFormat_ARGB32,
  /** Invalid color format. */
  NvBufferColorFormat_Invalid,
} NvBufferColorFormat;

/**
 * Defines video flip methods.
 */
typedef enum
{
  /** Video flip none. */
  NvBufferTransform_None,
  /** Video flip rotate 90 degree clockwise. */
  NvBufferTransform_Rotate90,
  /** Video flip rotate 180 degree clockwise. */
  NvBufferTransform_Rotate180,
  /** Video flip rotate 270 degree clockwise. */
  NvBufferTransform_Rotate270,
  /** Video flip with respect to X-axis. */
  NvBufferTransform_FlipX,
  /** Video flip with respect to Y-axis. */
  NvBufferTransform_FlipY,
  /** Video flip transpose. */
  NvBufferTransform_Transpose,
  /** Video flip inverse transpode. */
  NvBufferTransform_InvTranspose,
} NvBufferTransform_Flip;

/**
 * Defines transform video filter types.
 */
typedef enum
{
  /** transform filter nearest. */
  NvBufferTransform_Filter_Nearest,
  /** transform filter bilinear. */
  NvBufferTransform_Filter_Bilinear,
  /** transform filter 5 tap. */
  NvBufferTransform_Filter_5_Tap,
  /** transform filter 10 tap. */
  NvBufferTransform_Filter_10_Tap,
  /** transform filter smart. */
  NvBufferTransform_Filter_Smart,
  /** transform filter nicest. */
  NvBufferTransform_Filter_Nicest,
} NvBufferTransform_Filter;

/**
 * Defines flags to indicate for valid transform.
 */
typedef enum {
  /** transform flag to crop source rectangle. */
  NVBUFFER_TRANSFORM_CROP_SRC   = 1,
  /** transform flag to crop destination rectangle. */
  NVBUFFER_TRANSFORM_CROP_DST   = 1 << 1,
  /** transform flag to set filter type. */
  NVBUFFER_TRANSFORM_FILTER     = 1 << 2,
  /** transform flag to set flip method. */
  NVBUFFER_TRANSFORM_FLIP       = 1 << 3,
} NvBufferTransform_Flag;

/**
 * Defines flags to indicate for valid composition/blending operation.
 */
typedef enum {
  /** flag to set for composition. */
  NVBUFFER_COMPOSITE  = 1,
  /** flag to set for blending. */
  NVBUFFER_BLEND      = 1 << 1,
} NvBufferComposite_Flag;

/**
 * Defines composition background r,g,b colors.
 */
typedef struct
{
  /** background color value for r. */
  float r;
  /** background color value for g. */
  float g;
  /** background color value for b. */
  float b;
}NvBufferCompositeBackground;

/**
 * Defines coordinates for rectangle.
 */
typedef struct
{
  /** rectangle top. */
  uint32_t top;
  /** rectangle left. */
  uint32_t left;
  /** rectangle width. */
  uint32_t width;
  /** rectangle height. */
  uint32_t height;
}NvBufferRect;

/**
 * Defines parameters related to hardware buffer.
 */
typedef struct _NvBufferParams
{
  /** dmabuf_fd of hardware buffer. */
  uint32_t dmabuf_fd;
  /** pointer to hardware buffer memory. */
  void *nv_buffer;
  /** size of hardware buffer. */
  uint32_t nv_buffer_size;
  /** video format type of hardware buffer. */
  uint32_t pixel_format;
  /** number of planes of hardware buffer. */
  uint32_t num_planes;
  /** width of each planes of hardware buffer. */
  uint32_t width[MAX_NUM_PLANES];
  /** height of each planes of hardware buffer. */
  uint32_t height[MAX_NUM_PLANES];
  /** pitch of each planes of hardware buffer. */
  uint32_t pitch[MAX_NUM_PLANES];
  /** memory offset values of each video planes of hardware buffer. */
  uint32_t offset[MAX_NUM_PLANES];
  /** size of each vodeo planes of hardware buffer. */
  uint32_t psize[MAX_NUM_PLANES];
  /** layout type of each planes of hardware buffer. */
  uint32_t layout[MAX_NUM_PLANES];
}NvBufferParams;

/**
 * Defines parameters related to composition/blending.
 */
typedef struct _NvBufferCompositeParams
{
  /** flag to indicate which of the composition/blending parameters are valid. */
  uint32_t composite_flag;
  /** number of the input buffers to be composited. */
  uint32_t input_buf_count;
  /** alpha values of input buffers for the blending. */
  float dst_comp_rect_alpha[MAX_COMPOSITE_FRAME];
  /** source rectangle coordinates of input buffers for composition. */
  NvBufferRect src_comp_rect[MAX_COMPOSITE_FRAME];
  /** destination rectangle coordinates of input buffers for composition. */
  NvBufferRect dst_comp_rect[MAX_COMPOSITE_FRAME];
  /** background color values for composition. */
  NvBufferCompositeBackground composite_bgcolor;
}NvBufferCompositeParams;

/**
 * Defines parameters related to transform.
 */
typedef struct _NvBufferTransformParams
{
  /** flag to indicate which of the transform parameters are valid. */
  uint32_t transform_flag;
  /** flip method. */
  NvBufferTransform_Flip transform_flip;
  /** transform filter. */
  NvBufferTransform_Filter transform_filter;
  /** source rectangle coordinates for crop opeartion. */
  NvBufferRect src_rect;
  /** destination rectangle coordinates for crop opeartion. */
  NvBufferRect dst_rect;
}NvBufferTransformParams;

/**
* This method must be used for getting `EGLImage` from `dmabuf-fd`.
*
* @param[in] display `EGLDisplay` object used during the creation of `EGLImage`.
* @param[in] dmabuf_fd `DMABUF FD` of buffer from which `EGLImage` to be created.
*
* @returns `EGLImageKHR` for success, `NULL` for failure
*/
EGLImageKHR NvEGLImageFromFd (EGLDisplay display, int dmabuf_fd);

/**
* This method must be used for destroying `EGLImage` object.

* @param[in] display `EGLDisplay` object used for destroying `EGLImage`.
* @param[in] eglImage `EGLImageKHR` object to be destroyed.
*
* @returns 0 for success, -1 for failure
*/
int NvDestroyEGLImage (EGLDisplay display, EGLImageKHR eglImage);

/**
 * Use this method to allocate HW buffer.
 * @param[out] dmabuf_fd Returns `dmabuf_fd` of hardware buffer.
 * @param[in] width Hardware buffer width, in bytes.
 * @param[in] height Hardware buffer height, in bytes.
 * @param[in] layout Layout of buffer.
 * @param[in] colorFormat The `colorFormat` of buffer.
 *
 * @returns 0 for success, -1 for failure
 */
int NvBufferCreate (int *dmabuf_fd, int width, int height,
    NvBufferLayout layout, NvBufferColorFormat colorFormat);

/**
 * Use this method to get buffer parameters.
 * @param[in] dmabuf_fd `DMABUF FD` of buffer.
 * @param[out] params A pointer to the structure to fill with parameters.
 *
 * @returns 0 for success, -1 for failure.
 */
int NvBufferGetParams (int dmabuf_fd, NvBufferParams *params);

/**
* This method must be used for destroying `hw_buffer`.
* @param[in] dmabuf_fd Specifies the `dmabuf_fd` `hw_buffer` to destroy.
*
* @returns 0 for success, -1 for failure.
*/
int NvBufferDestroy (int dmabuf_fd);

/**
* This method must be used to extract dmabuf_fd of the hardware buffer.
* @param[in] nvbuf Specifies the `hw_buffer`.
* @param[out] dmabuf_fd Returns DMABUF FD of `hw_buffer`.
*
* @returns 0 for success, -1 for failure.
*/
int ExtractFdFromNvBuffer (void *nvbuf, int *dmabuf_fd);

/**
* This method must be used for releasing dmabuf_fd.
* Obtained using ExtractfdFromNvBuffer API.
* @param[in] dmabuf_fd Specifies the `dmabuf_fd` to release.
*
* @returns 0 for success, -1 for failure.
*/
int NvReleaseFd (int dmabuf_fd);

/**
* This method must be used for hw memory cache sync for the CPU.
* @param[in] dmabuf_fd DMABUF FD of buffer.
* @param[in] plane video frame plane.
* @param[in] pVirtAddr Virtual Addres pointer of the mem mapped plane.
*
* @returns 0 for success, -1 for failure.
*/
int NvBufferMemSyncForCpu (int dmabuf_fd, unsigned int plane, void **pVirtAddr);

/**
* This method must be used for hw memory cache sync for device.
* @param[in] dmabuf_fd DMABUF FD of buffer.
* @param[in] plane video frame plane.
* @param[in] pVirtAddr Virtual Addres pointer of the mem mapped plane.
*
* @returns 0 for success, -1 for failure.
*/
int NvBufferMemSyncForDevice (int dmabuf_fd, unsigned int plane, void **pVirtAddr);

/**
* This method must be used for getting mem mapped virtual Address of the plane.
* @param[in] dmabuf_fd DMABUF FD of buffer.
* @param[in] plane video frame plane.
* @param[in] memflag NvBuffer memory flag.
* @param[in] pVirtAddr Virtual Addres pointer of the mem mapped plane.
*
* @returns 0 for success, -1 for failure.
*/
int NvBufferMemMap (int dmabuf_fd, unsigned int plane, NvBufferMemFlags memflag, void **pVirtAddr);

/**
* This method must be used to Unmap the mapped virtual Address of the plane.
* @param[in] dmabuf_fd DMABUF FD of buffer.
* @param[in] plane video frame plane.
* @param[in] pVirtAddr mem mapped Virtual Addres pointer of the plane.
*
* @returns 0 for success, -1 for failure.
*/
int NvBufferMemUnMap (int dmabuf_fd, unsigned int plane, void **pVirtAddr);

/**
* This method is used to copy NvBuffer plane contents to raw buffer plane.
* @param[in] dmabuf_fd DMABUF FD of NvBuffer.
* @param[in] plane video frame plane.
* @param[in] out_width aligned width of the raw data plane.
* @param[in] out_height aligned height of the raw data plane.
* @param[in] ptr pointer to the output raw plane data.
*
* @returns 0 for success, -1 for failure.
*/
int NvBuffer2Raw (int dmabuf_fd, unsigned int plane, unsigned int out_width, unsigned int out_height, unsigned char *ptr);

/**
* This method is used to copy raw buffer plane contents to NvBuffer plane.
* @param[in] ptr pointer to the input raw plane data.
* @param[in] plane video frame plane.
* @param[in] in_width aligned width of the raw data plane.
* @param[in] in_height aligned height of the raw data plane.
* @param[in] dmabuf_fd DMABUF FD of NvBuffer.
*
* @returns 0 for success, -1 for failure.
*/
int Raw2NvBuffer (unsigned char *ptr, unsigned int plane, unsigned int in_width, unsigned int in_height, int dmabuf_fd);

/**
 * This method is used to transform one DMA buffer to another DMA buffer.
 * It can support transforms for copying, scaling, fliping, rotation and cropping.
 * @param[in] src_dmabuf_fd DMABUF FD of source buffer
 * @param[in] dst_dmabuf_fd DMABUF FD of destination buffer
 * @param[in] transform_params transform parameters
 *
 * @return 0 for sucess, -1 for failure.
 */
int NvBufferTransform (int src_dmabuf_fd, int dst_dmabuf_fd, NvBufferTransformParams *transform_params);

/**
 * This method is used to composite multiple input DMA buffers to one output DMA buffer.
 * It can support composition of multiple input frames to one composited output.
 * @param[in] src_dmabuf_fds array of DMABUF FDs of source buffers to composite from
 * @param[in] dst_dmabuf_fd DMABUF FD of destination buffer for composition
 * @param[in] composite_params composition parameters
 *
 * @return 0 for sucess, -1 for failure.
 */
int NvBufferComposite (int *src_dmabuf_fds, int dst_dmabuf_fd, NvBufferCompositeParams *composite_params);
/** @} */
#ifdef __cplusplus
}
#endif

#endif
