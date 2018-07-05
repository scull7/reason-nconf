open Jest;

describe("Stringify should return a json string", () =>
  Expect.(
    test("stringify should properly stringify an object", () => {
      let testStr = Js.Dict.empty();
      Js.Dict.set(testStr, "str", Js.Json.string("test"));
      let testDict = Js.Dict.empty();
      Js.Dict.set(testDict, "obj", Js.Json.object_(testStr));
      let testObj = Js.Json.object_(testDict);
      let expected = {|module.exports = {
  "obj": {
    "str": "test"
  }
};|};
      let actual = JsFormat.stringify(testObj);
      expect(actual) |> toBe(expected);
    })
  )
);

describe("Parse should return a Js.Dict.t(Js.Json.t)", () =>
  Expect.(
    test("Simple test object", () => {
      let testInput = {|
      module.exports = {
        obj: {
          str: "test"
        }
      }
    |};
      let expected = "test";
      JsFormat.parse(testInput)
      |> Js.Dict.get(_, "obj")
      |> Belt.Option.flatMap(_, Js.Json.decodeObject)
      |> Belt.Option.flatMap(_, x => Js.Dict.get(x, "str"))
      |> Belt.Option.flatMap(_, Js.Json.decodeString)
      |> (
        actual =>
          switch (actual) {
          | None => fail("Could not decode string")
          | Some(str) => expect(str) |> toBe(expected)
          }
      );
    })
  )
);
