Utils.import "style/app.css";

type route =
  | DISCOVER
  | LISTALL;

type action =
  | ToggleShown
  | PeopleReceived Model.people;

type state = {
  people: Model.people,
  shown: route
};

let initialState () => {people: [], shown: LISTALL};

let nextRoute =
  fun
  | LISTALL => DISCOVER
  | DISCOVER => LISTALL;

let routeToString =
  fun
  | LISTALL => "Show All"
  | DISCOVER => "Discover";

let reducer action state =>
  switch action {
  | ToggleShown => ReasonReact.Update {...state, shown: nextRoute state.shown}
  | PeopleReceived people => ReasonReact.Update {...state, people}
  };

let component = ReasonReact.reducerComponent "App";

let peopleReceived people => PeopleReceived people;

let toggleShown _ => ToggleShown;

let make _children => {
  ...component,
  initialState,
  reducer,
  didMount: fun {reduce} => {
    Backend.getPeople (reduce peopleReceived);
    NoUpdate
  },
  render: fun {state: {people, shown}, reduce} =>
    <div className="App">
      <header>
        <AppBar shown=(shown |> nextRoute |> routeToString) onClick=(reduce toggleShown) />
      </header>
      <main>
        (
          switch people {
          | [] => ReasonReact.nullElement
          | _ =>
            switch shown {
            | DISCOVER => <Discover people />
            | LISTALL => <ListAll people />
            }
          }
        )
      </main>
    </div>
};
