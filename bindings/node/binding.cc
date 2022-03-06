#include "tree_sitter/parser.h"
#include <napi.h>

extern "C" TSLanguage * tree_sitter_sql();

namespace {

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports["_language"] = Napi::External<TSLanguage>::New(env, tree_sitter_sql());
  return exports;
}

NODE_API_MODULE(tree_sitter_sql_binding, Init)

}  // namespace
