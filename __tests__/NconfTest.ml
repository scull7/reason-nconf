open Jest

let () =
describe "Set should set a value using the : syntax" (fun () ->
  let config =
    Nconf.(
      make ()
      |> jsFilePathNamed "data" {|./__tests__/assets/data.js|}
    )
  in
  let open Expect in
  test "should set the given string value" (fun () ->
    let updated =
      Nconf.(
        config
        |> setLiteral "obj:host" (`Str "127.0.0.1")
        |> get ()
      )
    in
    expect updated##obj##host |> toBe "127.0.0.1"
  );

  test "should set the given object value" (fun () ->
    let updated =
      Nconf.(
        config
        |> setObject "thing" [%bs.obj { foo = "bar" }]
        |> get ()
      )
    in
    expect updated##thing##foo |> toBe "bar"
  )
);
