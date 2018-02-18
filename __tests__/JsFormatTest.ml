open Jest

let () =
describe "Stringify should return a json string" (fun () ->
  let open Expect in
  test "stringify should properly stringify an object" (fun () ->
    let testObj = [%bs.obj {
      obj = [%bs.obj {
        str = "test"
      }]
    }]
    in
    let expected = {|module.exports = {
  "obj": {
    "str": "test"
  }
};|}
    in
    let actual = JsFormat.stringify(testObj)
    in
    expect actual |> toBe expected
  )
);

describe "Parse should return a javascript object" (fun () ->
  let open Expect in
  test "simple test object" (fun () ->
    let testInput = {|
      module.exports = {
        obj: {
          str:"test"
        }
      }
    |} in
    let expected = [%bs.obj {
      obj = [%bs.obj {
        str = "test"
      }]
    }] in
    let actual = JsFormat.parse testInput in
    let _ = Js.log2 "ACTUAL" actual in
    expect actual |> ExpectJs.toMatchObject expected
  )
);
