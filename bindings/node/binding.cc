#include "tree_sitter/parser.h"
#include <node.h>
#include "napi.h"

extern "C" TSLanguage * tree_sitter_sql();

namespace {

struct Language : public Napi::ObjectWrap<Language> {
  TSLanguage* lang;

  Language(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Language>{info}, lang{tree_sitter_sql()} {}
  static Napi::FunctionReference& Constructor() {
    static Napi::FunctionReference ref;
    return ref;
  }
  static void Init(Napi::Env env, Napi::Object exports) {
    Napi::Function wrappedCtor = DefineClass(env, "Language", {});
    wrappedCtor["name"] = Napi::String::New(env, "sql");
    exports["Language"] = wrappedCtor;
    Constructor() = Napi::Persistent(wrappedCtor);
    Constructor().SuppressDestruct();
    tree_sitter_sql();
  }
};

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  Language::Init(env, exports);
  return exports;
}

NODE_API_MODULE(tree_sitter_sql_binding, Init)

}  // namespace
