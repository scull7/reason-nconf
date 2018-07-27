/* Only providing the standard JSON.stringify, if you need more options, implement your own :) */
[@bs.scope "JSON"] [@bs.val]
external jsonStringify : (Js.Json.t, Js.null('b), int) => string =
  "stringify";

type vmOptions = {
  .
  "lineOffset": int,
  "displayErrors": bool,
};

[@bs.deriving abstract]
type commonjs = {exports: Js.Dict.t(Js.Json.t)};

[@bs.deriving abstract]
type context = {
  [@bs.as "module"]
  module_: commonjs,
};

[@bs.module "vm"]
external runInNewContext : (string, context, vmOptions) => unit = "";

let stringify = config => {
  let prefix = "module.exports =";
  let jsonString = jsonStringify(config, Js.null, 2);
  {j|$prefix $jsonString;|j};
};

let parse = input => {
  let options = {"lineOffset": 0, "displayErrors": true};
  let context = ref(context(~module_=commonjs(~exports=Js.Dict.empty())));
  runInNewContext(input, context^, options);
  let ctx = context^;
  ctx |. module_Get |. exportsGet;
};
