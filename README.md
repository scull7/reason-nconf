# reason-nconf
ReasonML bindings to the nconf library.


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
