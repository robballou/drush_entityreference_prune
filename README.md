# Drush Entity Reference Prune

Helps prune duplicate entity reference values.

## Usage

**STEP 0: BACKUP THE DATABASE:** This command will delete data, if needed, from your database so data will be lost.

    drush entityreference-prune [field name]
    drush erp [field_name]

## Install

    pushd ~/.drush/
    git clone https://github.com/robballou/drush_entityreference_prune.git
    popd
    drush cache-clear drush
