type nconf;

[@bs.new] [@bs.module "nconf"]
external make : unit => nconf = "Provider";

[@bs.send.pipe : nconf] external overrides : 'a => nconf = "";

[@bs.send.pipe : nconf]
external env : unit => nconf = "";

[@bs.send.pipe : nconf]
external argv : unit => nconf = "";

[@bs.send.pipe : nconf]
external filePathAnon : string => nconf = "file";

[@bs.send.pipe : nconf]
external filePathNamed : (string, string) => nconf = "file";

[@bs.send.pipe : nconf]
external defaults : 'a => nconf = "";

[@bs.send.pipe : nconf]
external get : unit => 'a = "";
