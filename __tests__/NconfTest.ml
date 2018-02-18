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

describe "getKey should return the value at the given key" (fun () ->
  let config =
    Nconf.(
      make()
      |> jsFilePathNamed "data" {|./__tests__/assets/data.js|}
    )
  in
  let open Expect in
  test "it should return the value at an existing key" (fun () ->
    match (Js.Nullable.to_opt (Nconf.getKey config "obj:auth:username")) with
    | None -> (fail "key not found")
    | Some x -> expect x |> toBe "admin"
  );
  test "it should work for integer values too" (fun () ->
    match (Js.Nullable.to_opt (Nconf.getKey config "obj:port")) with
    | None -> (fail "key not found")
    | Some x -> expect x |> toBe 5984
  );
  test "it should return null on a non-existant key" (fun () ->
    match (Js.Nullable.to_opt (Nconf.getKey config "obj:auth:not_here")) with
    | None -> pass
    | Some x -> (fail {j|Got unexpected value: $x|j})
  );
);
