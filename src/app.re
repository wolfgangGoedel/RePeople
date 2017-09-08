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

let peopleReceived people => PeopleReceived people;

let toggleShown _ => ToggleShown;

let component = ReasonReact.reducerComponent "App";

let make _children => {
  ...component,
  initialState: fun () => {people: [||], shown: LISTALL},
  reducer,
  didMount: fun self => {
    Backend.getPeople (self.reduce peopleReceived);
    ReasonReact.NoUpdate
  },
  render: fun self => {
    let {people, shown} = self.state;
    let loaded = Array.length people > 0;
    <div className="App">
      <header>
        <AppBar shown=(shown |> nextRoute |> routeToString) onClick=(self.reduce toggleShown) />
      </header>
      <main>
        (
          if loaded {
            switch shown {
            | DISCOVER => <Discover people />
            | LISTALL => <ListAll people />
            }
          } else {
            ReasonReact.nullElement
          }
        )
      </main>
    </div>
  }
};
