open Model;

type actions =
  | Search(string);

type state = {filterPattern: string};

let initialState = () => {filterPattern: ""};

let reducer = (action, _state) =>
  switch action {
  | Search(pattern) => ReasonReact.Update({filterPattern: pattern})
  };

let component = ReasonReact.reducerComponent("ListAll");

let filterPerson = pattern => {
  open Js.Re;
  let re = fromStringWithFlags(pattern, ~flags="i");
  ({firstname, lastname}) => test(firstname, re) || test(lastname, re);
};

let personCards = (pattern, people) =>
  people
  |> List.filter(filterPerson(pattern))
  |> List.map(person => <PersonCard person key=person.id />);

let getValue = event => (
                          event
                          |> ReactEventRe.Form.target
                          |> ReactDOMRe.domElementToObj
                        )##value;

let make = (~people, _children) => {
  ...component,
  initialState,
  reducer,
  render: ({state: {filterPattern}, send}) =>
    <div>
      <div className="card-container">
        (
          people
          |> personCards(filterPattern)
          |> Array.of_list
          |> ReasonReact.arrayToElement
        )
      </div>
      <div className="control-container">
        <SearchInput
          id="searchInput"
          label="Search"
          value=filterPattern
          onChange=(event => send(Search(event |> getValue)))
        />
      </div>
    </div>
};