// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// When used in conjunction with module_embedder.h, this gives a default
// implementation of ppp.h for clients of the ppapi C++ interface.  Most
// plugin implementors can export their derivation of Module by just
// linking to this implementation.

#include "ppapi/c/ppb.h"
#include "ppapi/c/ppp.h"
#include "ppapi/c/pp_errors.h"
#include "ppapi/cpp/module.h"
#include "ppapi/cpp/module_embedder.h"

static pp::Module* g_module_singleton = NULL;

namespace pp {

// Give a default implementation of Module::Get().  See module.cc for details.
pp::Module* Module::Get() {
  return g_module_singleton;
}

}  // namespace pp

// Global PPP functions --------------------------------------------------------

PP_EXPORT int PPP_InitializeModule(PP_Module module_id,
                                   PPB_GetInterface get_browser_interface) {
  pp::Module* module = CreateModule();
  if (!module)
    return PP_Error_Failed;

  if (!module->InternalInit(module_id, get_browser_interface)) {
    delete module;
    return PP_Error_Failed;
  }
  g_module_singleton = module;
  return PP_OK;
}

PP_EXPORT void PPP_ShutdownModule() {
  delete g_module_singleton;
  g_module_singleton = NULL;
}

PP_EXPORT const void* PPP_GetInterface(const char* interface_name) {
  if (!g_module_singleton)
    return NULL;
  return g_module_singleton->GetInstanceInterface(interface_name);
}
