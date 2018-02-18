open Jest

type config = <
  foo: string;
  moo: string;
  boo: int
> Js.t

let () =
let base_dir =
  match [%bs.node __dirname] with
  | None -> Js.Exn.raiseError "Not running in a NodeJS context, no current dir"
  | Some p -> p
in
describe "jsFilePathNamed should parse a JavaScript file." (fun () ->
  let open Expect in
  test "should load the assets/test.js configuration file" (fun () ->
    let appConfig: config =
      Nconf.(
        make ()
        |> jsFilePathNamed "reasonml" {j|$base_dir/assets/test.js|j}
        |> get ()
        )
    in
    expect appConfig
    |> ExpectJs.toMatchObject [%obj { foo = "bar"; moo = "cow"; boo = 42 }]
  )
);
