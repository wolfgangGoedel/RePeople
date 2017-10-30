let getPeople = (callback: Model.people => unit) =>
  Js.Promise.(
    Bs_fetch.fetch("people.json")
    |> then_(Bs_fetch.Response.json)
    |> then_((people) => Model.Decode.people(people) |> callback |> resolve)
  )
  |> ignore;
