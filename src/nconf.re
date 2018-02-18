type nconf;

type format;

[@bs.new] [@bs.module "nconf"] external make : unit => nconf = "Provider";

[@bs.send.pipe : nconf] external overrides : 'a => nconf = "";

[@bs.send.pipe : nconf] external env : unit => nconf = "";

[@bs.send.pipe : nconf] external argv : unit => nconf = "";

[@bs.send.pipe : nconf] external filePathAnon : string => nconf = "file";

[@bs.send.pipe : nconf]
external filePathNamed : (string, string) => nconf = "file";

type formatter('a) = {
  .
  "stringify": Js.t('a) => string,
  "parse": string => Js.t('a)
};

type fileOptions('a) = {
  .
  "name": string,
  "file": string,
  "format": formatter('a)
};

[@bs.send.pipe : nconf]
external namedFileWithFormat : fileOptions('a) => nconf = "file";

[@bs.send.pipe : nconf] external defaults : 'a => nconf = "";

[@bs.send.pipe : nconf] external get : unit => 'a = "";

[@bs.send] external getKey : (nconf, string) => Js.Nullable.t('a) = "get";

[@bs.send] external setObject : (nconf, string, Js.t('a)) => unit = "set";

[@bs.send]
external setLiteral :
  (nconf, string, [@bs.unwrap] [ | `Str(string) | `Int(int)]) => unit =
  "set";

let jsFilePathNamed = (name, path, nconf) => {
  let jsFormat = {"stringify": JsFormat.stringify, "parse": JsFormat.parse};
  nconf
  |> namedFileWithFormat({"name": name, "file": path, "format": jsFormat});
};

let setLiteral = (key, value, nconf) => {
  setLiteral(nconf, key, value);
  nconf;
};

let setObject = (key, obj, nconf) => {
  setObject(nconf, key, obj);
  nconf;
};
