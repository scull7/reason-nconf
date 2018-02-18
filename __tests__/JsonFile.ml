open Jest

type config = <
  _APPNAME: string;
  _THING1: string;
  _THING2: string
> Js.t

let () =
let base_dir =
  match [%bs.node __dirname] with
  | None -> Js.Exn.raiseError "Not running in a NodeJS context, no current dir"
  | Some p -> p
in
describe "filePathNamed should parse a JSON file." (fun () ->
  let open Expect in
  test "should load the assets/test.json configuration file" (fun () ->
    let expected = [%bs.obj {
      _APPNAME = "reason-nconf";
      _THING1 = "red fish";
      _THING2 = 42
    }] in
    let appConfig: config =
      Nconf.(
        make ()
        |> filePathNamed "example" {j|$base_dir/assets/test.json|j}
        |> get ()
        )
    in
    expect appConfig
    |> ExpectJs.toMatchObject expected
  )
);
