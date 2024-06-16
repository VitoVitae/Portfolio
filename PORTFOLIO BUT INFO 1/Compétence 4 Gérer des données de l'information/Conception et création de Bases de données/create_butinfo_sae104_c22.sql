drop schema if exists programme_but cascade;
create schema programme_but;
set schema 'programme_but';

CREATE TABLE _competences (
  lib_competence  CHAR(30),
  CONSTRAINT competences_pk PRIMARY KEY(lib_competence)
);

CREATE TABLE _activites (
  lib_activite  CHAR(3),
  lib_competence  CHAR(3),
  CONSTRAINT activites_pk PRIMARY KEY(lib_activite),
  CONSTRAINT activites_fk_competences FOREIGN KEY(lib_competence) REFERENCES _competences(lib_competence)
);
  
CREATE TABLE _niveau (
  numero_n INTEGER NOT NULL,
  CONSTRAINT niveau_pk PRIMARY KEY(numero_n)
);

CREATE TABLE _parcours (
  code_p  CHAR(3),
  libelle_parcours CHAR(30),
  nbre_gpe_td_p INTEGER NOT NULL,
  nbre_gpe_tp_p INTEGER NOT NULL,
  CONSTRAINT parcours_pk PRIMARY KEY(code_p)
);

CREATE TABLE _semestre (
  numero_sem VARCHAR(30),
  numero_n INTEGER,
  CONSTRAINT semestre_pk PRIMARY KEY (numero_sem),
  CONSTRAINT semestre_fk_niveau FOREIGN KEY(numero_n) REFERENCES _niveau(numero_n)
);

CREATE TABLE _ressources (
  code_r VARCHAR(30),
  lib_r VARCHAR(30),
  nb_h_td_pn int,
  nb_h_tp_pn int,
  nb_h_cm_pn int,
  numero_sem VARCHAR(30),
  CONSTRAINT ressources_pk PRIMARY KEY (code_r),
  CONSTRAINT ressources_fk_semestre FOREIGN KEY(numero_sem) REFERENCES _semestre(numero_sem)
);


CREATE TABLE est_enseignee (
  code_p  CHAR(3),
  code_r CHAR(3),
  CONSTRAINT est_enseignee_pk PRIMARY KEY(code_p,code_r),
  CONSTRAINT est_enseignee_fk_parcours FOREIGN KEY(code_p) REFERENCES _parcours(code_p),
  CONSTRAINT est_enseignee_fk_ressources FOREIGN KEY(code_r) REFERENCES _ressources(code_r)
);

CREATE TABLE correspond (
  lib_activite  CHAR(30),
  code_p  CHAR(3),
  numero_n INTEGER NOT NULL,
  CONSTRAINT correspond_pk PRIMARY KEY(lib_activite, code_p, numero_n),
  CONSTRAINT correspond_fk_activites FOREIGN KEY(lib_activite) REFERENCES _activites(lib_activite),
  CONSTRAINT correspond_fk_niveau FOREIGN KEY(numero_n) REFERENCES _niveau(numero_n),
  CONSTRAINT correspond_fk_parcours FOREIGN KEY(code_p) REFERENCES _parcours(code_p)
);

CREATE TABLE _sae (
  code_sae VARCHAR(30),
  lib_sae VARCHAR(30),
  nb_h_td_enc int,
  nb_h_td_projet_autonomie int,
  CONSTRAINT sae_pk PRIMARY KEY (code_sae)
);

CREATE TABLE _ue (
  code_ue VARCHAR(30),
  numero_sem VARCHAR(30),
  lib_activite CHAR(3),
  CONSTRAINT ue_pk PRIMARY KEY (code_ue),
  CONSTRAINT ue_fk_semestre FOREIGN KEY(numero_sem) REFERENCES _semestre(numero_sem),
  CONSTRAINT ue_fk_activites FOREIGN KEY(lib_activite) REFERENCES _activites(lib_activite)
);

CREATE TABLE comprend_R (
  nb_h_td_c int,
  nb_h_tp_c int,
  code_sae VARCHAR(30),
  code_r VARCHAR(30),
  CONSTRAINT comprend_r_pk PRIMARY KEY (code_sae, code_r),
  CONSTRAINT comprend_r_fk_sae FOREIGN KEY (code_sae) REFERENCES _sae(code_sae),
  CONSTRAINT comprend_r_fk_ressources FOREIGN KEY (code_r) REFERENCES _ressources(code_r)
);
