let getPeople = (callback: Model.people => unit) =>
  Js.Promise.(
    Fetch.fetch("people.json")
    |> then_(Fetch.Response.json)
    |> then_((people) => Model.Decode.people(people) |> callback |> resolve)
  )
  |> ignore;