// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_C_PPP_FIND_H_
#define PPAPI_C_PPP_FIND_H_

#include "ppapi/c/pp_instance.h"

#define PPP_FIND_INTERFACE "PPP_Find;1"

typedef struct _ppp_Find {
  // Finds the given UTF-8 text starting at the current selection. The number of
  // results will be updated asynchronously via NumberOfFindResultsChanged in
  // PPB_Find. Note that multiple StartFind calls can happen before StopFind is
  // called in the case of the search term changing.
  //
  // Return false if plugin doesn't support find in page. Consequently, it won't
  // call any callbacks.
  bool (*StartFind)(PP_Instance instance,
                    const char* text,
                    bool caseSensitive);

  // Go to the next/previous result.
  void (*SelectFindResult)(PP_Instance instance,
                           bool forward);

  // Tells the plugin that the find operation has stopped, so it should clear
  // any highlighting.
  void (*StopFind)(PP_Instance instance);
} PPP_Find;

#endif  // PPAPI_C_PPP_FIND_H_