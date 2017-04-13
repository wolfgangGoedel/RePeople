external mapP : ('a => 'b) => Js.promise 'b 'f = "then" [@@bs.send.pipe : Js.promise 'a 'e];

external thenP : ('a => Js.promise 'b 'f) => Js.promise 'b 'f =
  "then" [@@bs.send.pipe : Js.promise 'a 'e];

let getPeople callback =>
  Bs_fetch.fetch "people.json"
  |> thenP Bs_fetch.Response.json
  |> mapP Model.jsonToPeople
  |> mapP callback
  |> ignore;