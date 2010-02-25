// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
// This file has been modified by Garrett R.
// Copyright (c) 2010 Garrett R. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "meta_table.h"

#include "connection.h"
#include "statement.h"
//#include "base/logging.h"

namespace sql {

// Key used in our meta table for version numbers.
static const char kVersionKey[] = "version";
static const char kCompatibleVersionKey[] = "last_compatible_version";

// static
bool MetaTable::DoesTableExist(const sql::Connection& db) {
  return db.DoesTableExist("meta");
}

MetaTable::MetaTable() : db_(NULL) {
}

MetaTable::~MetaTable() {
}

bool MetaTable::Init(Connection* db, int version, int compatible_version) {
  //DCHECK(!db_ && db);
  if (db_ || !db)
    return false;

  db_ = db;
  if (!DoesTableExist(*db_)) {
    if (!db_->Execute("CREATE TABLE meta"
        "(key LONGVARCHAR NOT NULL UNIQUE PRIMARY KEY,"
         "value LONGVARCHAR)"))
      return false;

    // Note: there is no index over the meta table. We currently only have a
    // couple of keys, so it doesn't matter. If we start storing more stuff in
    // there, we should create an index.
    SetVersionNumber(version);
    SetCompatibleVersionNumber(compatible_version);
  }
  return true;
}

bool MetaTable::SetValue(const char* key, const std::string& value) {
  Statement s;
  if (!PrepareSetStatement(&s, key))
    return false;
  s.BindString(1, value);
  return s.Run();
}

bool MetaTable::GetValue(const char* key, std::string* value) const {
  Statement s;
  if (!PrepareGetStatement(&s, key))
    return false;

  *value = s.ColumnString(0);
  return true;
}

bool MetaTable::SetValue(const char* key, int value) {
  Statement s;
  if (!PrepareSetStatement(&s, key))
    return false;

  s.BindInt(1, value);
  return s.Run();
}

bool MetaTable::GetValue(const char* key, int* value) const {
  Statement s;
  if (!PrepareGetStatement(&s, key))
    return false;

  *value = s.ColumnInt(0);
  return true;
}

bool MetaTable::SetValue(const char* key, int64 value) {
  Statement s;
  if (!PrepareSetStatement(&s, key))
    return false;
  s.BindInt64(1, value);
  return s.Run();
}

bool MetaTable::GetValue(const char* key, int64* value) const {
  Statement s;
  if (!PrepareGetStatement(&s, key))
    return false;

  *value = s.ColumnInt64(0);
  return true;
}

void MetaTable::SetVersionNumber(int version) {
  SetValue(kVersionKey, version);
}

int MetaTable::GetVersionNumber() const {
  int version = 0;
  if (!GetValue(kVersionKey, &version))
    return 0;
  return version;
}

void MetaTable::SetCompatibleVersionNumber(int version) {
  SetValue(kCompatibleVersionKey, version);
}

int MetaTable::GetCompatibleVersionNumber() const {
  int version = 0;
  if (!GetValue(kCompatibleVersionKey, &version))
    return 0;
  return version;
}

bool MetaTable::PrepareSetStatement(Statement* statement, const char* key) {
  if (!db_ || !statement)
    return false;

  statement->Assign(db_->GetCachedStatement(SQL_FROM_HERE,
      "INSERT OR REPLACE INTO meta (key,value) VALUES (?,?)"));
  if (!statement->is_valid()) {
    //NOTREACHED() << db_->GetErrorMessage();
    return false;
  }
  statement->BindCString(0, key);
  return true;
}

bool MetaTable::PrepareGetStatement(Statement* statement,
    const char* key) const {
  if (!db_ || !statement)
    return false;

  // Statement is non-mutating, so this cast is OK.
  statement->Assign(const_cast<sql::Connection*>(db_
      )->GetCachedStatement(SQL_FROM_HERE,
      "SELECT value FROM meta WHERE key=?"));
  if (!statement->is_valid()) {
    //NOTREACHED() << db_->GetErrorMessage();
    return false;
  }
  statement->BindCString(0, key);
  if (!statement->Step())
    return false;
  return true;
}

}  // namespace sql
