create table projects
(
    id integer not null primary key,
    name text not null,
    description text,
    customer integer references customers (id),
    deadline real,
    urgency integer,
    importance integer
);

create table tasks
(
    id integer not null primary key,
    project integer references projects (id),
    title text not null,
    description text,
    urgency integer,
    importance integer,
    -- original time estimate in hours
    hours_estimated_orig numeric,
    -- the original time estimate may be corrected
    -- while a task is being worked on, 
    hours_estimated_corrected numeric,
    hourly_rate integer check (hourly_rate >= 0),
    currency text references currencies (currency),
    percentage_done numeric,
    closed integer not null
);

-- stores all pairs of tasks (prerequisite, dependent)
-- such that dependent depends on prerequisite. 
create table task_depends
(
    prerequisite integer not null references task (id),
    dependent integer not null references task (id)
);

create table customers
(
    id integer not null primary key,
    name text not null,
    primary_contact text,
    primary_contact_email text,
    primary_contact_phone text,
    notes text
);

create table currencies
(
    currency text not null primary key
);

-- used to convert between dollars and cents, EUR and eurocents, etc.,
-- where the conversion factor is integral (100, most of the time),
-- to avoid floating point math.
create table currency_conversion
(
    curr1 text not null references currencies (currency),
    curr2 text not null references currencies (currency),
    factor integer not null
);

create table collaborators
(
    id integer not null primary key,
    -- this lacks a NOT NULL constraint because not all cultures
    -- have first and last names
    first_name text,
    last_name text not null,
    email text,
    phone text,
    form_of_address text,
    preferred_pronoun text
);

create table works_on
(
    collaborator integer not null references collaborator (id),
    task integer not null references task (id),
    booking integer references bookings (id)
);

create table bookings
(
    id integer not null primary key,
    start_time real,
    end_time real
);

create table teams
(
    id integer not null primary key,
    name text not null,
    description text
);

create table is_team_member
(
    collaborator integer not null references collaborators (id),
    team integer not null references teams (id),
    -- the role of the collaborator in the team,
    -- e.g. "team leader", "DBA", "web designer",
    -- could be a job title
    role text,
    -- a more detailed job description, if desired
    role_description text
);

create table is_project_member
(
    collaborator integer not null references collaborators (id),
    project integer not null references projects (id),
    role text,
    role_description text
);

-- Tag tables; every entity type that can be tagged
-- receives its own tag table.
-- To find entities of multiple types with the same tags,
-- just combine the tables with union (all).

create table project_tags
(
    project integer not null references projects (id),
    tag text not null
);

create table task_tags
(
    task integer not null references tasks (id),
    tag text not null
);

create table team_tags
(
    team integer not null references teams (id),
    tag text not null
);

create table collaborator_tags
(
    collaborator integer not null references collaborators (id),
    tag text not null
);

-- user account data
create table users
(
    id integer not null primary key,
    username text not null unique,
    -- hashed password
    pw_hash text not null,
    -- ...and the salt used for hashing
    salt text not null
);

-- resolve relation between users and collaborators
create table user_collaborator_mapping
(
    user integer not null references users(id),
    collaborator integer not null references collaborators(id)
);

create view time_spent_on_tasks as select
    end_time - start_time as time,
    collaborator,
    task
    from bookings join works_on
    on bookings.id = works_on.booking;

create view total_time_on_tasks as select
    sum(time) as total_time,
    collaborator,
    task
    from time_spent_on_tasks
    group by task, collaborator;

create view total_time_on_project as select
    sum(time) as total_time,
    collaborator,
    project
    from time_spent_on_tasks join tasks 
    on tasks.id = time_spent_on_tasks.task
    group by project, collaborator;

create view task_costs as select
    task,
    sum(total_time * hourly_rate) as cost
    from total_time_on_tasks join tasks
    on tasks.id = task;
