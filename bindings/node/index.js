const path = require("path");

// always use prebuilds since locally I test in electron and node
function loadBindingsWithPreloads(pkg) {
  const prevEnvValue = process.env.PREBUILDS_ONLY;
  process.env.PREBUILDS_ONLY = "1";
  const loadBindings = require("node-gyp-build");
  process.env.PREBUILDS_ONLY = prevEnvValue;
  delete require.cache[require.resolve("node-gyp-build")];
  // re-require every time to prevent PREBUILDS only from being used

  const result = loadBindings(pkg);
  return result;
}

module.exports = loadBindingsWithPreloads(path.join(__dirname, "../.."));

try {
  module.exports.nodeTypeInfo = require("../../src/node-types.json");
} catch (_) {}
