[@ocaml.ppx.context
  {
    tool_name: "migrate_driver",
    include_dirs: [],
    load_path: [],
    open_modules: [],
    for_package: None,
    debug: false,
    use_threads: false,
    use_vmthreads: false,
    recursive_types: false,
    principal: false,
    transparent_modules: false,
    unboxed_types: false,
    unsafe_string: false,
    cookies: [],
  }
];
module Color = {
  type t =
    | Red
    | Green
    | Blue;
  let parse = json =>
    switch (json |> Js.Json.decodeString) {
    | Some("green") => Green
    | Some("blue") => Blue
    | Some("red")
    | Some(_)
    | None => Red
    };
  let serialize = color =>
    (
      switch (color) {
      | Red => "red"
      | Green => "green"
      | Blue => "blue"
      }
    )
    |> Js.Json.string;
};
module DateTime = {
  type t = Js.Date.t;
  let parse = json =>
    switch (json |> Js.Json.decodeString) {
    | Some(str) => str |> Js.Date.fromString
    | None => Js.Date.make()
    };
  let serialize = date => date |> Js.Date.toISOString |> Js.Json.string;
};
module MyQuery' = {
  module Raw = {
    type t_customFields = {
      __typename: string,
      currentTime: Js.Json.t,
      favoriteColor: Js.Json.t,
      futureTime: Js.Nullable.t(Js.Json.t),
      nullableColor: Js.Nullable.t(Js.Json.t),
    };
    type t = {customFields: t_customFields};
    type t_variables = Js.Json.t;
  };
  let query = "query   {\ncustomFields  {\n__typename  \ncurrentTime  \nfavoriteColor  \nfutureTime  \nnullableColor  \n}\n\n}\n";
  type t_customFields = {
    __typename: string,
    currentTime: DateTime.t,
    favoriteColor: Color.t,
    futureTime: option(DateTime.t),
    nullableColor: option(Color.t),
  };
  type t = {customFields: t_customFields};
  type t_variables = Js.Json.t;
  let parse: Raw.t => t =
    (value) => (
      {
        customFields: {
          let value = (value: Raw.t).customFields;
          (
            {
              __typename: {
                let value = (value: Raw.t_customFields).__typename;
                value;
              },
              currentTime: {
                let value = (value: Raw.t_customFields).currentTime;
                DateTime.parse(value);
              },
              favoriteColor: {
                let value = (value: Raw.t_customFields).favoriteColor;
                Color.parse(value);
              },
              futureTime: {
                let value = (value: Raw.t_customFields).futureTime;
                switch (Js.toOption(value)) {
                | Some(value) => Some(DateTime.parse(value))
                | None => None
                };
              },
              nullableColor: {
                let value = (value: Raw.t_customFields).nullableColor;
                switch (Js.toOption(value)) {
                | Some(value) => Some(Color.parse(value))
                | None => None
                };
              },
            }: t_customFields
          );
        },
      }: t
    );
  let serialize: t => Raw.t =
    (value) => (
      {
        let customFields = {
          let value = (value: t).customFields;
          (
            {
              let nullableColor = {
                let value = (value: t_customFields).nullableColor;
                switch (value) {
                | Some(value) => Js.Nullable.return(Color.serialize(value))
                | None => Js.Nullable.null
                };
              }
              and futureTime = {
                let value = (value: t_customFields).futureTime;
                switch (value) {
                | Some(value) =>
                  Js.Nullable.return(DateTime.serialize(value))
                | None => Js.Nullable.null
                };
              }
              and favoriteColor = {
                let value = (value: t_customFields).favoriteColor;
                Color.serialize(value);
              }
              and currentTime = {
                let value = (value: t_customFields).currentTime;
                DateTime.serialize(value);
              }
              and __typename = {
                let value = (value: t_customFields).__typename;
                value;
              };
              {
                __typename,
                currentTime,
                favoriteColor,
                futureTime,
                nullableColor,
              };
            }: Raw.t_customFields
          );
        };
        {customFields: customFields};
      }: Raw.t
    );
  module Z__INTERNAL = {
    type root = t;
    type nonrec graphql_module;
    /****--- GraphQL PPX Module ---**

The contents of this module are automatically generated by `graphql-ppx`.
The following is simply an overview of the most important variables and types that you can access from this module.

```
module MyQuery {
  // This is the stringified representation of your query, which gets sent to the server.
  let query: string;

  // This is the main type of the result you will get back.
  // You can hover above the identifier key (e.g. query or mutation) to see the fully generated type for your module.
  type t;

  // This function turns your raw result from the server into the reason/ocaml representation of that result.
  // Depending on your graphql client library, this process should happen automatically for you.
  let parse: Raw.t => t;

  // This function will prepare your data for sending it back to the server.
  // Depending on your graphql client library, this process should happen automatically for you.
  let serialize: t => Raw.t;

  // The definition tuple is primarily used to interact with client libraries.
  // The types are equivalent to: (parse, query, serialize).
  // Your client library will use these values to provide the properly parsed / serialized data for you.
  let definition: (
    Raw.t => t,
    string,
    t => Raw.t
  );

  // This is the representation of your raw result coming from the server.
  // It should not be necessary to access the types inside for normal use cases.
  module Raw: { type t; };
}
```*/
    let graphql_module: graphql_module = Obj.magic(0);
  };
};
module MyQuery = {
  include MyQuery';
  module type query_type = (module type of MyQuery');
  let self: module query_type = (module MyQuery');
};
