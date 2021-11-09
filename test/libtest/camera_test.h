/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Copyright (C) 2019, Google Inc.
 *
 * camera_test.h - libcamera camera test base class
 */
#ifndef __LIBCAMERA_CAMERA_TEST_H__
#define __LIBCAMERA_CAMERA_TEST_H__

#include <memory>

#include <libcamera/camera.h>
#include <libcamera/camera_manager.h>

class CameraTest
{
public:
	CameraTest(const char *name, bool isolate = false);
	~CameraTest();

protected:
	libcamera::CameraManager *cm_;
	std::shared_ptr<libcamera::Camera> camera_;
	int status_;
};

#endif /* __LIBCAMERA_CAMERA_TEST_H__ */