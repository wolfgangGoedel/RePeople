let getPeople () =>
  Bs_fetch.fetch "people.json"
  |> Bs_promise.andThen Bs_fetch.Response.json
  |> Bs_promise.then_ Model.jsonToPeople;