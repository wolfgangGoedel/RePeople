let getPeople () =>
  Js.Promise.(
    Bs_fetch.fetch "people.json"
      |> then_ Bs_fetch.Response.json
      |> then_ (fun jsonPeople => Model.jsonToPeople jsonPeople |> resolve)
  );
