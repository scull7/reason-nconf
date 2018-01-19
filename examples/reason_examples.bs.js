'use strict';

var Nconf        = require("nconf");
var Js_exn       = require("bs-platform/lib/js/js_exn.js");
var Node_process = require("bs-platform/lib/js/node_process.js");

var match = typeof (__dirname) === "undefined" ? undefined : (__dirname);

var baseDir = match !== undefined ? match : Js_exn.raiseError("Not running in NodeJS context, no, current dir");

Node_process.putEnvVar("THING1", "42");

var appConfig = new Nconf.Provider().argv().env().file("example", "" + (String(baseDir) + "/example.json")).get();

console.log(appConfig);

exports.baseDir   = baseDir;
exports.appConfig = appConfig;
/* match Not a pure module */
