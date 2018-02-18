type config = {
  .
  "_APPNAME": string,
  "_THING1": string,
  "_THING2": int
};

let baseDir =
  switch [%bs.node __dirname] {
  | None => Js.Exn.raiseError("Not running in NodeJS context, no, current dir")
  | Some(path) => path
  };

let _ = Node.Process.putEnvVar("THING1", "42");

let appConfig: config =
  Nconf.(
    make()
    |> argv()
    |> env()
    |> filePathNamed("example", {j|$baseDir/example.json|j})
    |> get()
  );

Js.log(appConfig);
