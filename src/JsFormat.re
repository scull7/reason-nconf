/* Only providing the standard JSON.stringify, if you need more options, implement your own :) */
[@bs.scope "JSON"] [@bs.val]
external jsonStringify : (Js.t('a), Js.null('b), int) => string =
  "stringify";

type vmOptions = {
  .
  "lineOffset": int,
  "displayErrors": bool,
};

type context('a) = Js.t('a);

[@bs.module "vm"]
external runInNewContext : (string, context('a), vmOptions) => unit = "";

let stringify = config => {
  let prefix = "module.exports =";
  let jsonString = jsonStringify(config, Js.null, 2);
  {j|$prefix $jsonString;|j};
};

let parse = input => {
  let options = {"lineOffset": 0, "displayErrors": true };
  let context = ref({
                  "_module": {
                    "exports": Js.Obj.empty(),
                  },
                });
  runInNewContext(input, context^, options);
  let ctx = context^;
  ctx##_module##exports;
};
