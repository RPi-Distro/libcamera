# SPDX-License-Identifier: CC0-1.0

rpi_ipa_controller_sources = files([
    'algorithm.cpp',
    'controller.cpp',
    'device_status.cpp',
    'histogram.cpp',
    'pwl.cpp',
    'rpi/af.cpp',
    'rpi/agc.cpp',
    'rpi/alsc.cpp',
    'rpi/awb.cpp',
    'rpi/black_level.cpp',
    'rpi/ccm.cpp',
    'rpi/contrast.cpp',
    'rpi/dpc.cpp',
    'rpi/geq.cpp',
    'rpi/lux.cpp',
    'rpi/noise.cpp',
    'rpi/sdn.cpp',
    'rpi/sharpen.cpp',
])

rpi_ipa_controller_deps = [
    libcamera_private,
]

rpi_ipa_controller_lib = static_library('rpi_ipa_controller', rpi_ipa_controller_sources,
                                        dependencies : rpi_ipa_controller_deps)