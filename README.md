[![NPM](https://nodei.co/npm/reason-nconf.png?downloads=true&downloadRank=true&stars=true)](https://nodei.co/npm/reason-nconf/)
[![Build Status](https://www.travis-ci.org/scull7/reason-nconf.svg?branch=master)](https://www.travis-ci.org/scull7/reason-nconf)
[![Coverage Status](https://coveralls.io/repos/github/scull7/reason-nconf/badge.svg?branch=master)](https://coveralls.io/github/scull7/reason-nconf?branch=master)

# reason-nconf
ReasonML bindings to the [nconf][node-nconf] library.

This is a very rough implementation that will enable very simple use cases.

## Usage
```reason
type config = {
  ..
  "THING1": string,
  "THING2": int
};

let baseDir = "/path/to/somewhere"
let appConfig: config =
  Nconf.(
    make()
    |> argv()
    |> env()
    |> filePathNamed("locals", {j|$baseDir/config/locals.json|j})
    |> filePathNamed("defaults", {j|$baseDir/config/defaults.json|j})
    |> get()
  );
```

### Load a JavaScript file
This is accomplished from an internal module written in ReasonML.  The internal
module is a near 1-to-1 copy of [nconf-js]
```reason
let appConfig =
  Nconf.(
    make()
    |> jsFilePathNamed("example", {j|/path/to/file.js|j})
    |> get()
  );
```

### Set a value
#### String Literal
```reason
let appConfig =
  Nconf.(
    make()
    |> setLiteral("some:key:path", `Str("foo"))
    |> get()
  )
```
#### Integer Literal
```reason
let appConfig =
  Nconf.(
    make()
    |> setLiteral("some:key:path", `Int(42))
    |> get()
  )
```
#### Object Literal
```reason
let appConfig =
  Nconf.(
    make()
    |> setObject("some:key:path", { "foo": "bar" })
    |> get()
  )
```

## How do I install it?

Inside of a BuckleScript project:
```shell
yarn install --save reason-nconf
```

Then add `reason-nconf` to your `bs-dependencies` in `bsconfig.json`:
```json
{
  "bs-dependencies": [
    "reason-nconf"
  ]
}
```

## How do I use it?

See the [Usage](#usage) section above...

## What's missing?

Mostly everything...

[node-nconf]: https://www.npmjs.com/package/nconf
[nconf-js]: https://github.com/yoneal/nconf-js
