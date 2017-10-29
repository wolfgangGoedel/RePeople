module Decode = {
  let person = (json) : Model.person =>
    Json.Decode.{
      id: json |> field("id", string),
      firstname: json |> field("firstname", string),
      lastname: json |> field("lastname", string),
      photoUrl: json |> field("photo", string),
      entity: json |> field("entity", string),
      email: json |> field("email", string),
      phone: json |> field("phone", string),
      manager: json |> optional(field("entity", string))
    };
  let people = (json) => Json.Decode.(json |> list(person));
};

let getPeople = (callback: Model.people => unit) =>
  Js.Promise.(
    Bs_fetch.fetch("people.json")
    |> then_(Bs_fetch.Response.json)
    |> then_((jsonPeople) => jsonPeople |> Decode.people |> callback |> resolve)
  )
  |> ignore;
