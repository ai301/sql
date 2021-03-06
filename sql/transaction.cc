// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
// This file has been modified by Garrett R.
// Copyright (c) 2010 Garrett R. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "transaction.h"

#include "connection.h"
//#include "base/logging.h"

namespace sql {

Transaction::Transaction(Connection* connection)
    : connection_(connection),
      is_open_(false) {
}

Transaction::~Transaction() {
  if (is_open_)
    connection_->RollbackTransaction();
}

bool Transaction::Begin() {
  if (is_open_) {
    //NOTREACHED() << "Beginning a transaction twice!";
    return false;
  }
  is_open_ = connection_->BeginTransaction();
  return is_open_;
}

bool Transaction::Rollback() {
  if (!is_open_) {
    //NOTREACHED() << "Attempting to roll back a nonexistant transaction. "
    //             << "Did you remember to call Begin() and check its return?";
    return false;
  }
  is_open_ = connection_->RollbackTransaction();
  return is_open_;
}

bool Transaction::Commit() {
  if (!is_open_) {
    //NOTREACHED() << "Attempting to commit a nonexistant transaction. "
    //             << "Did you remember to call Begin() and check its return?";
    return false;
  }
  is_open_ = false;
  return connection_->CommitTransaction();
}

}  // namespace sql
