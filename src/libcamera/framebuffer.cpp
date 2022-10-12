/* SPDX-License-Identifier: LGPL-2.1-or-later */
/*
 * Copyright (C) 2019, Google Inc.
 *
 * framebuffer.cpp - Frame buffer handling
 */

#include <libcamera/framebuffer.h>
#include "libcamera/internal/framebuffer.h"

#include <libcamera/base/log.h>

/**
 * \file libcamera/framebuffer.h
 * \brief Frame buffer handling
 *
 * \file libcamera/internal/framebuffer.h
 * \brief Internal frame buffer handling support
 */

namespace libcamera {

LOG_DEFINE_CATEGORY(Buffer)

/**
 * \struct FrameMetadata
 * \brief Metadata related to a captured frame
 *
 * The FrameMetadata structure stores all metadata related to a captured frame,
 * as stored in a FrameBuffer, such as capture status, timestamp and bytesused.
 */

/**
 * \enum FrameMetadata::Status
 * \brief Define the frame completion status
 * \var FrameMetadata::FrameSuccess
 * The frame has been captured with success and contains valid data. All fields
 * of the FrameMetadata structure are valid.
 * \var FrameMetadata::FrameError
 * An error occurred during capture of the frame. The frame data may be partly
 * or fully invalid. The sequence and timestamp fields of the FrameMetadata
 * structure is valid, the other fields may be invalid.
 * \var FrameMetadata::FrameCancelled
 * Capture stopped before the frame completed. The frame data is not valid. All
 * fields of the FrameMetadata structure but the status field are invalid.
 */

/**
 * \struct FrameMetadata::Plane
 * \brief Per-plane frame metadata
 *
 * Frames are stored in memory in one or multiple planes. The
 * FrameMetadata::Plane structure stores per-plane metadata.
 */

/**
 * \var FrameMetadata::Plane::bytesused
 * \brief Number of bytes occupied by the data in the plane, including line
 * padding
 *
 * This value may vary per frame for compressed formats. For uncompressed
 * formats it will be constant for all frames, but may be smaller than the
 * FrameBuffer size.
 */

/**
 * \var FrameMetadata::status
 * \brief Status of the frame
 *
 * The validity of other fields of the FrameMetadata structure depends on the
 * status value.
 */

/**
 * \var FrameMetadata::sequence
 * \brief Frame sequence number
 *
 * The sequence number is a monotonically increasing number assigned to the
 * frames captured by the stream. The value is increased by one for each frame.
 * Gaps in the sequence numbers indicate dropped frames.
 */

/**
 * \var FrameMetadata::timestamp
 * \brief Time when the frame was captured
 *
 * The timestamp is expressed as a number of nanoseconds relative to the system
 * clock since an unspecified time point.
 *
 * \todo Be more precise on what timestamps refer to.
 */

/**
 * \fn FrameMetadata::planes()
 * \copydoc FrameMetadata::planes() const
 */

/**
 * \fn FrameMetadata::planes() const
 * \brief Retrieve the array of per-plane metadata
 * \return The array of per-plane metadata
 */

/**
 * \class FrameBuffer::Private
 * \brief Base class for FrameBuffer private data
 *
 * The FrameBuffer::Private class stores all private data associated with a
 * framebuffer. It implements the d-pointer design pattern to hide core
 * FrameBuffer data from the public API, and exposes utility functions to
 * pipeline handlers.
 */

FrameBuffer::Private::Private()
	: request_(nullptr), isContiguous_(true)
{
}

/**
 * \fn FrameBuffer::Private::setRequest()
 * \brief Set the request this buffer belongs to
 * \param[in] request Request to set
 *
 * For buffers added to requests by applications, this function is called by
 * Request::addBuffer() or Request::reuse(). For buffers internal to pipeline
 * handlers, it is called by the pipeline handlers themselves.
 */

/**
 * \fn FrameBuffer::Private::isContiguous()
 * \brief Check if the frame buffer stores planes contiguously in memory
 *
 * Multi-planar frame buffers can store their planes contiguously in memory, or
 * split them into discontiguous memory areas. This function checks in which of
 * these two categories the frame buffer belongs.
 *
 * \return True if the planes are stored contiguously in memory, false otherwise
 */

/**
 * \class FrameBuffer
 * \brief Frame buffer data and its associated dynamic metadata
 *
 * The FrameBuffer class is the primary interface for applications, IPAs and
 * pipeline handlers to interact with frame memory. It contains all the static
 * and dynamic information to manage the whole life cycle of a frame capture,
 * from buffer creation to consumption.
 *
 * The static information describes the memory planes that make a frame. The
 * planes are specified when creating the FrameBuffer and are expressed as a set
 * of dmabuf file descriptors, offset and length.
 *
 * The dynamic information is grouped in a FrameMetadata instance. It is updated
 * during the processing of a queued capture request, and is valid from the
 * completion of the buffer as signaled by Camera::bufferComplete() until the
 * FrameBuffer is either reused in a new request or deleted.
 *
 * The creator of a FrameBuffer (application, IPA or pipeline handler) may
 * associate to it an integer cookie for any private purpose. The cookie may be
 * set when creating the FrameBuffer, and updated at any time with setCookie().
 * The cookie is transparent to the libcamera core and shall only be set by the
 * creator of the FrameBuffer. This mechanism supplements the Request cookie.
 */

/**
 * \struct FrameBuffer::Plane
 * \brief A memory region to store a single plane of a frame
 *
 * Planar pixel formats use multiple memory regions to store the different
 * colour components of a frame. The Plane structure describes such a memory
 * region by a dmabuf file descriptor, an offset within the dmabuf and a length.
 * A FrameBuffer then contains one or multiple planes, depending on the pixel
 * format of the frames it is meant to store.
 *
 * The offset identifies the location of the plane data from the start of the
 * memory referenced by the dmabuf file descriptor. Multiple planes may be
 * stored in the same dmabuf, in which case they will reference the same dmabuf
 * and different offsets. No two planes may overlap, as specified by their
 * offset and length.
 *
 * To support DMA access, planes are associated with dmabuf objects represented
 * by FileDescriptor handles. The Plane class doesn't handle mapping of the
 * memory to the CPU, but applications and IPAs may use the dmabuf file
 * descriptors to map the plane memory with mmap() and access its contents.
 *
 * \todo Specify how an application shall decide whether to use a single or
 * multiple dmabufs, based on the camera requirements.
 */

/**
 * \var FrameBuffer::Plane::kInvalidOffset
 * \brief Invalid offset value, to identify uninitialized planes
 */

/**
 * \var FrameBuffer::Plane::fd
 * \brief The dmabuf file descriptor
 */

/**
 * \var FrameBuffer::Plane::offset
 * \brief The plane offset in bytes
*/

/**
 * \var FrameBuffer::Plane::length
 * \brief The plane length in bytes
 */

/**
 * \brief Construct a FrameBuffer with an array of planes
 * \param[in] planes The frame memory planes
 * \param[in] cookie Cookie
 */
FrameBuffer::FrameBuffer(const std::vector<Plane> &planes, unsigned int cookie)
	: Extensible(std::make_unique<Private>()), planes_(planes),
	  cookie_(cookie)
{
	metadata_.planes_.resize(planes_.size());

	unsigned int offset = 0;
	bool isContiguous = true;
	ino_t inode = 0;

	for (const auto &plane : planes_) {
		ASSERT(plane.offset != Plane::kInvalidOffset);

		if (plane.offset != offset) {
			isContiguous = false;
			break;
		}

		/*
		 * Two different dmabuf file descriptors may still refer to the
		 * same dmabuf instance. Check this using inodes.
		 */
		if (plane.fd.fd() != planes_[0].fd.fd()) {
			if (!inode)
				inode = planes_[0].fd.inode();
			if (plane.fd.inode() != inode) {
				isContiguous = false;
				break;
			}
		}

		offset += plane.length;
	}

	LOG(Buffer, Debug)
		<< "Buffer is " << (isContiguous ? "" : "not ") << "contiguous";

	_d()->isContiguous_ = isContiguous;
}

/**
 * \fn FrameBuffer::planes()
 * \brief Retrieve the static plane descriptors
 * \return Array of plane descriptors
 */

/**
 * \brief Retrieve the request this buffer belongs to
 *
 * The intended callers of this function are buffer completion handlers that
 * need to associate a buffer to the request it belongs to.
 *
 * A FrameBuffer is associated to a request by Request::addBuffer() and the
 * association is valid until the buffer completes. The returned request
 * pointer is valid only during that interval.
 *
 * \return The Request the FrameBuffer belongs to, or nullptr if the buffer is
 * not associated with a request
 */
Request *FrameBuffer::request() const
{
	return _d()->request_;
}

/**
 * \fn FrameBuffer::metadata()
 * \brief Retrieve the dynamic metadata
 * \return Dynamic metadata for the frame contained in the buffer
 */

/**
 * \fn FrameBuffer::cookie()
 * \brief Retrieve the cookie
 *
 * The cookie belongs to the creator of the FrameBuffer, which controls its
 * lifetime and value.
 *
 * \sa setCookie()
 *
 * \return The cookie
 */

/**
 * \fn FrameBuffer::setCookie()
 * \brief Set the cookie
 * \param[in] cookie Cookie to set
 *
 * The cookie belongs to the creator of the FrameBuffer. Its value may be
 * modified at any time with this function. Applications and IPAs shall not
 * modify the cookie value of buffers they haven't created themselves. The
 * libcamera core never modifies the buffer cookie.
 */

/**
 * \fn FrameBuffer::cancel()
 * \brief Marks the buffer as cancelled
 *
 * If a buffer is not used by a request, it shall be marked as cancelled to
 * indicate that the metadata is invalid.
 */

} /* namespace libcamera */