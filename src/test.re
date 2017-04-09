external (>>$) : Js.promise 'a 'e => ('a => 'b) => Js.promise 'b 'f = "then" [@@bs.send];

external (>>=) : Js.promise 'a 'e => ('a => Js.promise 'b 'f) => Js.promise 'b 'f =
  "then" [@@bs.send];

let fetchTest () => Bs_fetch.fetch "test.json" >>= Bs_fetch.Response.json >>$ Js.log;