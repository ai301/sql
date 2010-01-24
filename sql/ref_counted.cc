// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
// This file has been modified by Garrett R.
// Copyright (c) 2010 Garrett R. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ref_counted.h"

namespace base {

namespace subtle {

RefCountedBase::RefCountedBase()
    : ref_count_(0) {}

RefCountedBase::~RefCountedBase() {}

void RefCountedBase::AddRef() {
  // TODO(maruel): Add back once it doesn't assert 500 times/sec.
  // Current thread books the critical section "AddRelease" without release it.
  // DFAKE_SCOPED_LOCK_THREAD_LOCKED(add_release_);
  ++ref_count_;
}

bool RefCountedBase::Release() {
  // TODO(maruel): Add back once it doesn't assert 500 times/sec.
  // Current thread books the critical section "AddRelease" without release it.
  // DFAKE_SCOPED_LOCK_THREAD_LOCKED(add_release_);
  if (--ref_count_ == 0) {
    return true;
  }
  return false;
}

}  // namespace subtle

}  // namespace base
