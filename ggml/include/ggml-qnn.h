 /*
 * Copyright (c) 2024- KanTV Authors
 *
 * this is new implementation of ggml-qnn(ggml backend of Qualcomm Neural Network), https://github.com/zhouwg/kantv/issues/246
 *
 * Qualcomm QNN SDK and reference tech guides could be found at:
 * https://www.qualcomm.com/developer/software/qualcomm-ai-engine-direct-sdk
 * https://qpm.qualcomm.com/#/main/tools/details/qualcomm_ai_engine_direct
 * https://developer.qualcomm.com/software/hexagon-dsp-sdk/tools
 *
 */

 /*
 * Copyright (c) 2023-2024 The ggml authors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#pragma once

#include "ggml.h"
#include "ggml-backend.h"

#ifdef __cplusplus
extern "C" {
#endif


#define GGML_QNN_MAX_DEVICES    3
#define GGML_QNN_BACKEND_NAME   "qnn"

enum QNNBackend {
    QNN_BACKEND_CPU,
    QNN_BACKEND_GPU,
    QNN_BACKEND_NPU,
    QNN_BACKEND_GGML, //"fake" QNN backend for compare performance between QNN backend and cpu backend
};

GGML_BACKEND_API ggml_backend_t ggml_backend_qnn_init(size_t dev_num, const char * qnn_lib_path);

GGML_BACKEND_API bool           ggml_backend_is_qnn(ggml_backend_t backend);

GGML_BACKEND_API void           ggml_backend_qnn_set_n_threads(ggml_backend_t backend, int thread_counts);

GGML_BACKEND_API int            ggml_backend_qnn_get_device_count(void);

GGML_BACKEND_API ggml_backend_reg_t ggml_backend_qnn_reg(void);

inline const char * ggml_backend_qnn_get_devname(size_t dev_num) {
    switch (dev_num) {
        case QNN_BACKEND_CPU:
            return "QNN-CPU";
        case QNN_BACKEND_GPU:
            return "QNN-GPU";
        case QNN_BACKEND_NPU:
            return "QNN-NPU";
        case QNN_BACKEND_GGML:
            return "ggml"; //"fake" QNN backend, used for compare performance between QNN backend and original GGML
        default:
            return "unknown";
    }
}

#ifdef __cplusplus
}
#endif
