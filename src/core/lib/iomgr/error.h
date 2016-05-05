/*
 *
 * Copyright 2015, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef GRPC_CORE_LIB_IOMGR_ERROR_H
#define GRPC_CORE_LIB_IOMGR_ERROR_H

#include <stdint.h>

#include <grpc/support/time.h>

typedef struct grpc_error grpc_error;

typedef enum {
  GRPC_ERROR_INT_ERRNO,
  GRPC_ERROR_INT_FILE_LINE,
  GRPC_ERROR_INT_STATUS_CODE,
  GRPC_ERROR_INT_WARNING,
  GRPC_ERROR_INT_STREAM_ID,
  GRPC_ERROR_INT_GRPC_STATUS,
  GRPC_ERROR_INT_OFFSET,
  GRPC_ERROR_INT_INDEX,
  GRPC_ERROR_INT_SIZE,
} grpc_error_ints;

typedef enum {
  GRPC_ERROR_STR_DESCRIPTION,
  GRPC_ERROR_STR_FILE,
  GRPC_ERROR_STR_OS_ERROR,
  GRPC_ERROR_STR_SYSCALL,
  GRPC_ERROR_STR_TARGET_ADDRESS,
  GRPC_ERROR_STR_GRPC_MESSAGE,
  GRPC_ERROR_STR_RAW_BYTES,
} grpc_error_strs;

typedef enum {
  GRPC_ERROR_TIME_CREATED,
} grpc_error_times;

#define GRPC_ERROR_NONE ((grpc_error *)NULL)
#define GRPC_ERROR_OOM ((grpc_error *)1)
#define GRPC_ERROR_CANCELLED ((grpc_error *)2)

const char *grpc_error_string(grpc_error *error);
void grpc_error_free_string(const char *str);

grpc_error *grpc_error_create(const char *file, int line, const char *desc,
                              grpc_error **referencing, size_t num_referencing);
#define GRPC_ERROR_CREATE(desc) \
  grpc_error_create(__FILE__, __LINE__, desc, NULL, 0)
#define GRPC_ERROR_CREATE_REFERENCING(desc, errs, count) \
  grpc_error_create(__FILE__, __LINE__, desc, errs, count)
grpc_error *grpc_error_ref(grpc_error *err);
void grpc_error_unref(grpc_error *err);
grpc_error *grpc_error_set_int(grpc_error *src, grpc_error_ints which,
                               intptr_t value);
const intptr_t *grpc_error_get_int(grpc_error *error, grpc_error_ints which);
grpc_error *grpc_error_set_time(grpc_error *src, grpc_error_times which,
                                gpr_timespec value);
grpc_error *grpc_error_set_str(grpc_error *src, grpc_error_strs which,
                               const char *value);
grpc_error *grpc_error_add_child(grpc_error *src, grpc_error *child);
grpc_error *grpc_os_error(const char *file, int line, int err,
                          const char *call_name);
#define GRPC_OS_ERROR(err, call_name) \
  grpc_os_error(__FILE__, __LINE__, err, call_name)

#endif /* GRPC_CORE_LIB_IOMGR_ERROR_H */
