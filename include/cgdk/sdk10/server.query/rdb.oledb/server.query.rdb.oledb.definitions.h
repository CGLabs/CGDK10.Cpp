//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 10.0 / Release 2019.12.11                       *
//*                                                                           *
//*                        Server Query oledb Classes                         *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                (c) 2003. Cho Sanghyun. All right reserved.                *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

namespace CGDK
{
//----------------------------------------------------------------------------
//
//  query oledb classes
//
//----------------------------------------------------------------------------
namespace query
{
namespace rdb
{
namespace oledb
{
	void						_dump_error_records	(throwable::failure_ex& _e) noexcept;
	throwable::failure_ex		_dump_error_records	(HRESULT _result, const wstring_param _command) noexcept;
}
}
}

struct SERVER_QUERY_ERROR_INFO
{
	object_ptr<Iquerier>		pquerier;
	object_ptr<Iserver_query>	pquery;

	intptr_t					result;
	std::string_view			str_query;
	Ndescription_ex				exception;

	LCID						lcLocale;
	CDBErrorInfo				error_info;
};


//----------------------------------------------------------------------------
//
//  query oledb fuctions
//
//----------------------------------------------------------------------------
NUMERIC __to_numeric(const DB_NUMERIC& _decimal) noexcept;


}


//----------------------------------------------------------------------------
//
//  OLEDB error codes
//
//		0x80004005	Unspecified error
//
//    * 0x80040E
//		0x80040E00	The accessor is invalid.
//		0x80040E01	It was not possible to insert a row into the row set, because the maximum number of active rows for the provider would have been exceeded.
//		0x80040E02	The accessor is write-protected. The procedure has failed.
//		0x80040E03	Values violate the database schema.
//		0x80040E04	The row handle is invalid.
//		0x80040E05	The object was open.
//		0x80040E06	Invalid chapter
//		0x80040E07	A literal value in the command could not be converted to the correct type for a reason other than data overflow.
//		0x80040E08	Invalid binding information
//		0x80040E09	Permission denied
//		0x80040E0A	The specified column contains no bookmarks or chapters.
//		0x80040E0B	Some cost limitations were rejected.
//		0x80040E0C	No command was specified for the command object.
//		0x80040E0D	No query plan was found within the specified cost limitation.
//		0x80040E0E	Invalid bookmark
//		0x80040E0F	Invalid lock mode
//		0x80040E10	No value was specified for at least one of the required parameters.
//		0x80040E11	Invalid column ID
//		0x80040E12	Invalid quota
//		0x80040E13	Invalid value
//		0x80040E14	The command contained at least one error. (invalide word(ex. data,select ...), special character(ex. ./*:!#&-? ...)
//		0x80040E15	The currently executed command cannot be aborted.
//		0x80040E16	The provider offers no support for the specified dialect.
//		0x80040E17	A data source with the specified name already exists.
//		0x80040E18	The row set was created via a live datastream and cannot be restarted.
//		0x80040E19	In the current range no key matches the described characteristics.
//		0x80040E1B	The provider is unable to determine the identity for the newly added rows.
//		0x80040E1A	The ownership of this structure was transferred to the provider.
//		0x80040E1C	Non-zero weighting values are not supported as target information. The target was therefore rejected. The current target was not changed.
//		0x80040E1D	The requested conversion is not supported.
//		0x80040E1E	RowsOffset leads to position after the end of the row set, irrespective of the specified cRows value. cRowsObtained is 0.
//		0x80040E20	The provider has called an IRowsetNotify method in the consumer and has not yet received a return from the method.
//		0x80040E21	Error
//		0x80040E22	A non-zero controlling IUnknown object was specified, and the currently created object does not support aggregation.
//		0x80040E23	The current row was deleted.
//		0x80040E24	The row set does not support backward calls.
//		0x80040E25	All HROW objects have to be released before new HROW objects can be received.
//		0x80040E26	A specified memory flag was not supported.
//		0x80040E27	The comparison operator was invalid.
//		0x80040E28	The specified status flag was neither DBCOLUMNSTATUS_OK nor DBCOLUMNSTATUS_ISNULL.
//		0x80040E29	The row set cannot be processed backwards.
//		0x80040E2A	Invalid range handle.
//		0x80040E2B	The specified row set was not adjacent to the rows of the specified monitoring range, and there was no overlap.
//		0x80040E2C	A transition from ALL* to MOVE* or EXTEND* was specified.
//		0x80040E2D	The specified range is not a valid subrange of the range identified by the specified monitoring range handle.
//		0x80040E2E	The provider does not support commands with several statements.
//		0x80040E2F	A specified value violated the integrity restrictions for a column or table.
//		0x80040E30	The specified type name was not recognized.
//		0x80040E31	Execution was aborted, since no further resources were available. No results were returned.
//		0x80040E32	A command object with a command hierarchy containing at least one row set could not be cloned.
//		0x80040E33	The current structure cannot be shown as text.
//		0x80040E34	The specified index already exists.
//		0x80040E35	The specified index does not exist.
//		0x80040E36	The specified index was used.
//		0x80040E37	The specified table does not exist.
//		0x80040E38	The row set has uses fully parallelism, and the value of a column was changed since the last read operation.
//		0x80040E39	Errors were found during copying.
//		0x80040E3A	A precision statement was invalid.
//		0x80040E3B	A specified decimal value was invalid.
//		0x80040E3C	Invalid table ID.
//		0x80040E3D	A specified type was invalid.
//		0x80040E3E	A column ID occurred several times in the specification.
//		0x80040E3F	The specified table already exists.
//		0x80040E40	The specified table was used.
//		0x80040E41	The specified range schema ID was not supported.
//		0x80040E42	The specified record number is invalid.
//		0x80040E43	No matching row could be found, despite the fact that the bookmark formatting was valid.
//		0x80040E44	The value of a property was invalid.
//		0x80040E45	The row set was not subdivided into chapters.
//		0x80040E46	Invalid accessor
//		0x80040E47	Invalid memory flags
//		0x80040E48	Accessors for transfer as reference are not supported by this provider.
//		0x80040E49	NULL accessors are not supported by this provider.
//		0x80040E4A	The command was not prepared.
//		0x80040E4B	The specified accessor was not a parameter accessor.
//		0x80040E4C	The specified accessor was write-protected.
//		0x80040E4D	Error during authentication.
//		0x80040E4E	The change was aborted during the notification; no columns were modified.
//		0x80040E4F	The row set consisted of a chapter, but the chapter was not enabled.
//		0x80040E50	Invalid source handle
//		0x80040E51	The provider is unable to derive parameter information, and SetParameterInfo was not called.
//		0x80040E52	The data source object is already initialized.
//		0x80040E53	The provider does not support this method.
//		0x80040E54	The number of rows with pending modifications exceeds the specified limit.
//		0x80040E55	The specified column did not exist.
//		0x80040E56	Changes are pending in a row with a reference counter of zero.
//		0x80040E57	A literal value in the command let to a range violation for the type of the assigned column.
//		0x80040E58	The transferred HRESULT value was invalid.
//		0x80040E59	The transferred LookupID value was invalid.
//		0x80040E5A	The transferred DynamicErrorID value was invalid.
//		0x80040E5B	No visible data for a newly added row that has not yet been updated can be retrieved.
//		0x80040E5C	Invalid conversion flag
//		0x80040E5D	The specified parameter name was not recognized.
//		0x80040E5E	Several memory objects cannot be open simultaneously.
//		0x80040E5F	The requested filter could not be opened.
//		0x80040E60	The requested sequence could not be opened.
//		0x80040E65	The transferred columnID value was invalid.
//		0x80040E67	The transferred command has no DBID value.
//		0x80040E68	The transferred DBID value already exists.
//		0x80040E69	The maximum number of session objects supported by this provider has already been reached. The consumer must release at least one current session object, before a new session object can be retrieved.
//		0x80040E72	The index ID is invalid.
//		0x80040E73	The specified initialization character sequence does not match the specification.
//		0x80040E74	The OLE DB master enumerator has not returned any providers that match the requested SOURCES_TYPE value.
//		0x80040E75	The initialization character sequence indicates a provider that does not match the currently active provider.
//		0x80040E76	The specified DBID value is invalid.
//		0x80040E6A	Invalid value for trust recipient.
//		0x80040E6B	The trust recipient is not intended for the current data source.
//		0x80040E6C	The trust recipient offers no support for memberships/list.
//		0x80040E6D	The object is invalid, or the provider is unknown.
//		0x80040E6E	The object has no owner.
//		0x80040E6F	The transferred access entry list is invalid.
//		0x80040E70	The trust recipient transferred as owner is invalid, or the provider is unknown.
//		0x80040E71	The permission transferred in the access entry list is invalid.
//		0x80040E77	The ConstraintType value was invalid or was not supported by the provider.
//		0x80040E78	The ConstraintType value was not DBCONSTRAINTTYPE_FOREIGNKEY, and cForeignKeyColumns was not zero.
//		0x80040E79	The Deferability value was invalid or was not supported by the provider.
//		0x80040E80	The MatchType value was invalid or was not supported by the provider.
//		0x80040E8A	The UpdateRule or DeleteRule value was invalid or was not supported by the provider.
//		0x80040E8B	Invalid restriction ID.
//		0x80040E8C	The dwFlags value was invalid.
//		0x80040E8D	The rguidColumnType value pointed to a GUID that does not match the object type of this column, or this column was not specified.
//		0x80040E91	No source row exists.
//		0x80040E92	The OLE DB object represented by this URL is locked by at least one other process.
//		0x80040E93	The client requested an object type that is only for lists.
//		0x80040E94	The calling process requested write access for a write-protected object.
//		0x80040E95	The provider was unable to establish a connection with the server for this object.
//		0x80040E96	The provider was unable to establish a connection with the server for this object.
//		0x80040E97	Timeout during binding to the object
//		0x80040E98	The provider was unable to create an object with this URL, since an object named by this URL already exists.
//		0x80040E8E	The requested URL was outside the valid range.
//		0x80040E90	The column or restriction could not be deleted, since a dependent view or restriction refers to it.
//		0x80040E99	The restriction already exists.
//		0x80040E9A	The object cannot be created with this URL, since the server has insufficient physical memory.
//
//
//    * 0x0040
//		0x00040EC0	During retrieval of the requested number of rows the total number of active rows supported by this row set was exceeded.
//		0x00040EC1	At least one column type is not compatible; conversion errors may occur during copying.
//		0x00040EC2	Information on the parameter type were disabled by the calling process.
//		0x00040EC3	The bookmark for a deleted or irrelevant row was skipped.
//		0x00040EC5	No further row sets are available.
//		0x00040EC6	Start or end of the row set or chapter reached.
//		0x00040EC7	The command was executed again by the provider.
//		0x00040EC8	The data shared_buffer for the variable is full.
//		0x00040EC9	No further results are available.
//		0x00040ECA	The server is unable to cancel or downgrade a lockout until a transaction is complete.
//		0x00040ECB	The specified weighting value was not supported or exceeded the supported limit. The value was set to 0 or to the limit.
//		0x00040ECC	For this reason the consumer rejects further notification calls.
//		0x00040ECD	The input dialect was ignored, and the text was returned in another dialect.
//		0x00040ECE	The consumer rejects further notification calls for this phase.
//		0x00040ECF	For this reason the consumer rejects further notification calls.
//		0x00040ED0	The operation is processed asynchronously.
//		0x00040ED1	To reach the start of the row set, the provider has to execute the query again. Either the order of the columns has changed, or columns were added to the row set, or columns were removed from the row set.
//		0x00040ED2	The method had several errors. The errors were returned in the error array.
//		0x00040ED3	Invalid row handle
//		0x00040ED4	A specified HROW object referred to a permanently deleted row.
//		0x00040ED5	The provider was unable to trace all modifications. The client has to retrieve the data assigned the monitoring range again via another method.
//		0x00040ED6	The execution was terminated because no more resources were available. The results received up to this time were returned, but the execution cannot continue.
//		0x00040ED8	A lockout was upgraded relative to the specified value.
//		0x00040ED9	At least one property was changed according to the options permitted by the provider.
//		0x00040EDA	Error
//		0x00040EDB	A specified parameter was invalid.
//		0x00040EDC	Due to the update of this row several rows in the data source had to be updated.
//		0x00040ED7	The binding failed, since the provider was not able to meet all binding flags or properties.
//		0x00040EDD	The row contains no row-specific columns.
//
//----------------------------------------------------------------------------
