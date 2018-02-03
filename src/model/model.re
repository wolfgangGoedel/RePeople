type person = {
  id: string,
  firstname: string,
  lastname: string,
  photoUrl: string,
  entity: string,
  email: string,
  phone: string,
  manager: option(string)
};

type people = list(person);

module Decode = {
  open Json.Decode;
  let person = (json) => {
    id: json |> field("id", string),
    firstname: json |> field("firstname", string),
    lastname: json |> field("lastname", string),
    photoUrl: json |> field("photo", string),
    entity: json |> field("entity", string),
    email: json |> field("email", string),
    phone: json |> field("phone", string),
    manager: json |> optional(field("entity", string))
  };
  let people = (json) => json |> list(person);
};