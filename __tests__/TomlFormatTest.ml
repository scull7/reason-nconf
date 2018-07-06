open Jest

type seuss = {
  thing1: string;
  thing2: string;
} [@@bs.deriving abstract]

type config = {
  foo: string;
  moo: string;
  boo: int;
  things: string array;
  dr: seuss;
} [@@bs.deriving abstract]

let () =
let base_dir =
  match [%bs.node __dirname] with
  | None -> Js.Exn.raiseError "Not running in a NodeJS context, no current dir"
  | Some p -> p
in
describe "tomlFilePathNamed should parse a TOML file." (fun () ->
  let open Expect in
  test "should load the assets/test.toml configuration file." (fun () ->
    let app_config: config =
      Nconf.(
        make ()
        |> tomlFilePathNamed "toml" {j|$base_dir/assets/test.toml|j}
        |> get ()
      )
    in
    let _ = Js.log2("Config: ", app_config) in
    let expected =
      config
        ~foo:"bar"
        ~moo:"cow"
        ~boo: 42
        ~things: [|"red fish"; "blue fish"|]
        ~dr: (seuss ~thing1:"one fish" ~thing2:"two fish")
    in
    expect app_config
    |> ExpectJs.toEqual expected
  )
);

