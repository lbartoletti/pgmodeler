/*
# PostgreSQL Database Modeler (pgModeler)
#
# Copyright 2006-2021 - Raphael Araújo e Silva <raphael@pgmodeler.io>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation version 3.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# The complete text of GPLv3 is at LICENSE file on source code root directory.
# Also, you can get the complete GNU General Public License at <http://www.gnu.org/licenses/>
*/

/**
\ingroup libcore
\brief Implements the operations to manipulate operators on the database.
\note <strong>Creation date:</strong> 16/04/2008
*/

#ifndef OPERATOR_H
#define OPERATOR_H

#include "baseobject.h"
#include "function.h"
#include "schema.h"
#include "role.h"

class Operator: public BaseObject {
	private:
		//! \brief Stores the functions that defines the operator
		Function *functions[3];

		//! \brief Stores the arguments types (left and right) used by the operator
		PgSqlType argument_types[2];

		//! \brief Stores the auxiliary operators
		Operator *operators[2];

		bool	hashes, //! \brief Indicates that the operator can execute a hash join
		merges;  //! \brief Indicates that the operator can execute a merge join

	protected:
		virtual void configureSearchAttributes();

	public:
		static constexpr unsigned FuncOperator=0,
		FuncJoin=1,
		FuncRestrict=2,
		LeftArg=0,
		RightArg=1,
		OperCommutator=0,
		OperNegator=1;

		Operator();

		//! \brief Defines the name of the operator
		void setName(const QString &name);

		//! \brief Defines the function used by the operator (constants FUNC_[OPERATOR | JOIN | RESTRICT])
		void setFunction(Function *func, unsigned func_type);

		//! \brief Defines the argument data type for operator (constants ARG_[LEFT | RIGHT])
		void setArgumentType(PgSqlType arg_type, unsigned arg_id);

		//! \brief Defines the auxiliary operators (constants OPER_[COMMUTATOR | NEGATOR])
		void setOperator(Operator *oper, unsigned op_type);

		//! \brief Defines that the operator accepts hash join
		void setHashes(bool value);

		//! \brief Defines that the operator accepts merge join
		void setMerges(bool value);

		//! \brief Returns the function used by the operator referencing it by its type
		Function *getFunction(unsigned func_type);

		//! \brief Returns the type of the passed argument id
		PgSqlType getArgumentType(unsigned arg_id);

		//! \brief Returns on of the auxiliary operators
		Operator *getOperator(unsigned op_type);

		//! \brief Returns whether the operator accepts hash join
		bool isHashes();

		//! \brief Returns whether the operator accepts merge join
		bool isMerges();

		//! \brief Validates the passed name using the naming rule for operators
		static bool isValidName(const QString &name);

		//! \brief Returns the SQL / XML definition for the operator
		virtual QString getCodeDefinition(unsigned def_type, bool reduced_form) final;
		virtual QString getCodeDefinition(unsigned def_type) final;

		//! \brief Returns the operator signature
		virtual QString getSignature(bool format_name=true);
};

#endif
