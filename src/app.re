Utils.import "style/app.css";

open ReasonReact;

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
  | ToggleShown => Update {...state, shown: nextRoute state.shown}
  | PeopleReceived people => Update {...state, people}
  };

let peopleReceived people => PeopleReceived people;

let toggleShown _ => ToggleShown;

let initialState () => {people: [], shown: LISTALL};

let didMount {reduce} => {
  Backend.getPeople (reduce peopleReceived);
  NoUpdate
};

let render {state: {people, shown}, reduce} =>
  <div className="App">
    <header>
      <AppBar shown=(shown |> nextRoute |> routeToString) onClick=(reduce toggleShown) />
    </header>
    <main>
      (
        switch people {
        | [] => nullElement
        | _ =>
          switch shown {
          | DISCOVER => <Discover people />
          | LISTALL => <ListAll people />
          }
        }
      )
    </main>
  </div>;

let component = reducerComponent "App";

let make _children => {...component, initialState, reducer, didMount, render};
