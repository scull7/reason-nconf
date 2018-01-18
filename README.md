[![Project State](https://img.shields.io/badge/state-alpha-red.svg)]

# reason-nconf
ReasonML bindings to the nconf library.

This is a very rough implementation that will enable very simple use cases.

## Usage
```reason
type config = {
  ..
  "THING1": string,
  "THING2": int
}
 
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
