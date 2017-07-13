Random.self_init ();

let component = ReasonReact.statelessComponent "Discover";
let make people::(people: Model.people) _children => {
  ...component,
  render: fun _self => {
    <PersonCard person=people.(Random.int ((Array.length people) - 1)) />
  }
}
