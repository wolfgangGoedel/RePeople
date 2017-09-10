type people = list person
and person = {
  id: string,
  firstname: string,
  lastname: string,
  photoUrl: string,
  entity: string,
  email: string,
  phone: string,
  manager: option string
};

let jsonToPeople json => {
  let toPerson dict => {
    let decode key =>
      key |> Js_dict.get dict |> Utils.bindO Js.Json.decodeString |> Utils.unwrapUnsafely;
    let decodeOpt key => key |> Js_dict.get dict |> Utils.bindO Js.Json.decodeString;
    {
      id: "id" |> decode,
      firstname: "firstname" |> decode,
      lastname: "lastname" |> decode,
      photoUrl: "photo" |> decode,
      entity: "entity" |> decode,
      email: "email" |> decode,
      phone: "phone" |> decode,
      manager: "manager" |> decodeOpt
    }
  };
  let decodePerson p => p |> Js.Json.decodeObject |> Utils.unwrapUnsafely |> toPerson;
  json |> Js.Json.decodeArray |> Utils.unwrapUnsafely |> Array.map decodePerson |> Array.to_list
};
